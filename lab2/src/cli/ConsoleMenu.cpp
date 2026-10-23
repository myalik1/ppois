#include "../../include/cli/ConsoleMenu.h"
#include "../../include/exceptions/WorkflowExceptions.h"
#include <vector>

namespace docflow {

namespace {
const std::size_t kDefaultStorageBytes = 1048576;
const std::size_t kDefaultDocSizeBytes = 256;
const std::size_t kMaxAuditEntries = 500;
const std::size_t kMaxRegistryTags = 100;
const std::size_t kMinRequiredVersions = 1;
const int kInitialQuota = 50;
const int kSingleDocumentQuota = 1;
const int kDefaultSecurityLevel = 2;
const int kMinSecurityFilter = 1;
const int kAdminAccessLevel = 5;
const int kAdminRolePriority = 10;
const int kDefaultTagWeight = 3;
const int kHighConfidentialityWeight = 8;
const int kFirstVersionNumber = 1;
const int kFirstStepOrder = 1;
const int kCurrentDay = 10;
const int kArchiveStartDay = 5;
const int kCertExpiryDay = 365;
const int kDefaultRetentionDays = 180;
const int kDefaultContractDays = 30;
const int kContractExtensionDays = 15;
const int kMaxSlaHours = 24;
const int kDefaultProcessingHours = 4;
const int kExtraWorkflowHours = 2;
const int kDefaultReminderHour = 12;
const int kRescheduledReminderHour = 18;
const int kHighSeverityScore = 9;
const int kHashIterations = 3;
const long kInitialTimestamp = 100L;
const long kUpdatedTimestamp = 120L;
const double kDefaultTaxPercent = 20.0;
}

ConsoleMenu::ConsoleMenu()
    : defaultDepartment_("DEP-1", "InformationSecurity", "USR-1", kInitialQuota),
      defaultUser_("USR-1", "Kirill Admin", "admin@bsuir.by", "DEP-1", true),
      accessController_("AC-MAIN", true),
      defaultCert_("CERT-100", "USR-1", "BSUIR-CA", kCertExpiryDay, false),
      signatureService_("MainSign", CryptoHasher("SHA256", "SALT", kHashIterations)),
      activeFolder_("FLD-1", "ActiveDocs"),
      backupManager_("BackupNode-1"),
      tagRegistry_("MainTagRegistry", kMaxRegistryTags),
      searchEngine_("MainSearch"),
      notificationService_(NotificationChannel("EMAIL", "notify@bsuir.by", true)),
      complianceChecker_("MainCompliance"),
      workflowMetrics_(0, 0, 0),
      departmentStats_("DEP-1", 0, 0),
      slaMonitor_("StandardSLA", kMaxSlaHours, 0),
      system_(
          "EnterpriseDocFlow",
          AccessController("AC-INIT", true),
          DocumentRepository("MainRepo", StorageLocation("LOC-1", "/var/docs", kDefaultStorageBytes, 0)),
          WorkflowManager("WF-1"),
          AuditLogger("MainAudit", kMaxAuditEntries)) {
    initializeDefaultConfiguration();
}

void ConsoleMenu::initializeDefaultConfiguration() {
    Permission docPerm("PERM-DOC", "DOCUMENT", kAdminAccessLevel);
    Role adminRole("Administrator", kAdminRolePriority);
    adminRole.addPermission(docPerm);
    accessController_.assignRole(defaultUser_, adminRole);
    Tag defaultTag("Confidential", "Security", kHighConfidentialityWeight);
    tagRegistry_.registerTag(defaultTag);
    ComplianceRule baseRule("RULE-SIGN", kMinRequiredVersions, true);
    complianceChecker_.addRule(baseRule);
    StorageLocation mainLoc("LOC-1", "/var/docs", kDefaultStorageBytes, 0);
    DocumentRepository mainRepo("MainRepo", mainLoc);
    WorkflowManager wfManager("WF-1");
    AuditLogger auditLogger("MainAudit", kMaxAuditEntries);
    system_ = DocumentFlowSystem("EnterpriseDocFlow", accessController_, mainRepo, wfManager, auditLogger);
}

void ConsoleMenu::printMenu(std::ostream& output) const {
    output << "\n=== Система электронного документооборота ===\n"
           << "1. Зарегистрировать документ (версия, метаданные, вложение, тег)\n"
           << "2. Создать документ по шаблону и проверить права/квоты отдела\n"
           << "3. Оформить спецдокументы (Договор, Счёт, Приказ, Отчёт, Служебка)\n"
           << "4. Запустить маршрут согласования, эскалацию и утвердить документ\n"
           << "5. Подписать документ ЭЦП и сформировать штамп организации\n"
           << "6. Поместить в папку, сделать резервную копию и проверить архив\n"
           << "7. Поиск, фильтрация, сортировка документов и реестр тегов\n"
           << "8. Управление подписками, уведомлениями и напоминаниями\n"
           << "9. Аудит, проверка комплаенса и регистрация инцидентов ИБ\n"
           << "10. Сводная аналитика, проверка SLA и статус документа\n"
           << "0. Выход\n"
           << "Выберите пункт: ";
}

void ConsoleMenu::handleCreateDocument(std::istream& input, std::ostream& output) {
    std::string docId;
    std::string title;
    output << "Введите ID и название документа: ";
    input >> docId >> title;
    DocumentMetadata meta(kInitialTimestamp, kInitialTimestamp, "RU", kDefaultSecurityLevel);
    meta.updateModificationTime(kUpdatedTimestamp);
    Document doc(docId, title, defaultUser_.getUserId(), meta);
    DocumentVersion ver(kFirstVersionNumber, defaultUser_.getUserId(), "Initial text", "Init");
    doc.addNewVersion(ver);
    Attachment attachment("scan.pdf", "application/pdf", kDefaultDocSizeBytes, "CHK-1");
    doc.attachFile(attachment);
    Tag tag("Corporate", "General", kDefaultTagWeight);
    doc.applyTag(tag);
    system_.registerAndStoreDocument(defaultUser_, doc, kDefaultDocSizeBytes);
    searchEngine_.indexDocument(doc);
    departmentStats_.registerCreation();
    output << "Документ " << docId << " успешно сохранён.\n";
}

void ConsoleMenu::handleTemplateAndAccess(std::istream& input, std::ostream& output) {
    std::string docId;
    output << "Введите ID документа для создания по шаблону: ";
    input >> docId;
    defaultDepartment_.consumeQuota(kSingleDocumentQuota);
    DocumentTemplate tmpl("TPL-1", "OrderTpl", "Template {{BODY}}", kDefaultSecurityLevel);
    Document doc = tmpl.instantiateDocument(docId, "TemplateDoc", defaultUser_);
    system_.registerAndStoreDocument(defaultUser_, doc, kDefaultDocSizeBytes);
    searchEngine_.indexDocument(doc);
    bool hasAccess = accessController_.verifyAccess(defaultUser_, "DOCUMENT", kDefaultSecurityLevel);
    bool emailOk = defaultUser_.validateEmailFormat();
    output << "Шаблон создан для " << docId << " | Доступ: " << hasAccess
           << " | Email: " << emailOk << " | Квота: " << defaultDepartment_.getMonthlyQuota() << "\n";
}

void ConsoleMenu::handleSpecializedDocuments(std::istream& input, std::ostream& output) {
    std::string docId;
    double netAmount = 0.0;
    output << "Введите ID базового документа и сумму счёта: ";
    input >> docId >> netAmount;
    Document baseDoc = system_.getStoredDocument(docId);
    ContractDocument contract(baseDoc, "PartnerLLC", netAmount, kDefaultContractDays);
    contract.prolongContract(kContractExtensionDays);
    InvoiceDocument invoice(baseDoc, netAmount, kDefaultTaxPercent, false);
    double grossTotal = invoice.calculateGrossTotal();
    invoice.markAsPaid(grossTotal);
    OrderDocument order(baseDoc, "Directive", defaultDepartment_.getDepartmentId(), 1);
    ReportDocument report(baseDoc, "2026-Q4", 1, false);
    report.verifyReport(defaultUser_);
    MemoDocument memo(baseDoc, defaultUser_.getUserId(), defaultUser_.getUserId(), false);
    memo.escalateUrgency();
    output << "Спецдокументы оформлены. Счёт с НДС: " << grossTotal
           << " | Договор до дня: " << contract.getExpirationDay()
           << " | Приказ активен: " << order.isEffectiveOn(kCurrentDay) << "\n";
}

void ConsoleMenu::handleWorkflowAndApproval(std::istream& input, std::ostream& output) {
    std::string docId;
    output << "Введите ID документа для запуска согласования и утверждения: ";
    input >> docId;
    ApprovalRoute route("RT-1", "StandardApproval");
    ApprovalStep step(kFirstStepOrder, defaultUser_.getUserId());
    route.appendStep(step);
    system_.initiateDocumentApproval(defaultUser_, docId, route);
    EscalationRule rule("ESC-1", kMaxSlaHours, "USR-BACKUP");
    std::string approver = rule.resolveApprover(kDefaultProcessingHours, defaultUser_.getUserId());
    system_.approveDocumentInSystem(defaultUser_, docId, "Approved via CLI");
    WorkflowState state(docId, "APPROVED", kDefaultProcessingHours, false);
    state.advanceHours(kExtraWorkflowHours);
    output << "Маршрут согласования запущен и документ " << docId << " утверждён ("
           << approver << ", стадия: " << state.getStageName() << ").\n";
}

void ConsoleMenu::handleSignAndStamp(std::istream& input, std::ostream& output) {
    std::string docId;
    output << "Введите ID документа для подписания ЭЦП: ";
    input >> docId;
    Document doc = system_.getStoredDocument(docId);
    DigitalSignature sig = signatureService_.signDocument(
        doc, defaultUser_, defaultCert_, kCurrentDay);
    bool verified = signatureService_.verifyDocumentSignatures(
        doc, defaultCert_, kCurrentDay);
    OfficialStamp stamp("STAMP-01", "BSUIR", "REG-2026");
    std::string stampMark = stamp.formatStampMark();
    output << "Документ подписан. Хэш ЭЦП: " << sig.getSignatureHash()
           << " | Подлинность: " << verified << " | Штамп: " << stampMark << "\n";
}

void ConsoleMenu::handleStorageAndArchive(std::istream& input, std::ostream& output) {
    std::string docId;
    output << "Введите ID документа для архивации и резервного копирования: ";
    input >> docId;
    Document doc = system_.getStoredDocument(docId);
    activeFolder_.putDocument(doc);
    StorageLocation backupLoc("LOC-BAK", "/var/backup", kDefaultStorageBytes, 0);
    DocumentRepository backupRepo("BackupRepo", backupLoc);
    backupRepo.saveDocument(doc, kDefaultDocSizeBytes);
    backupManager_.createBackupSnapshot(backupRepo, docId);
    ArchivePolicy policy("StandardRetention", kDefaultRetentionDays, true);
    ArchiveRecord record("ARC-1", docId, kArchiveStartDay, policy.getPolicyName());
    bool canRestore = record.canRestore(policy, kCurrentDay);
    output << "В папке документов: " << activeFolder_.countDocuments()
           << " | Бэкапов: " << backupManager_.getSnapshotCount()
           << " | Доступен к восстановлению: " << canRestore << "\n";
}

void ConsoleMenu::handleSearchAndSort(std::istream& input, std::ostream& output) {
    std::string queryTerm;
    output << "Введите поисковый термин: ";
    input >> queryTerm;
    std::vector<std::string> foundIds = searchEngine_.searchByTerm(queryTerm);
    IndexEntry entry("IDX-1", {queryTerm}, kDefaultSecurityLevel);
    int score = entry.scoreTermMatch(queryTerm);
    SearchFilter filter(queryTerm, "", kMinSecurityFilter);
    DocumentSorter sorter("title", true);
    std::vector<Document> matchedDocs;
    for (const auto& id : foundIds) {
        matchedDocs.push_back(system_.getStoredDocument(id));
    }
    sorter.sortByTitle(matchedDocs);
    std::vector<Document> filtered = searchEngine_.filterDocuments(matchedDocs, filter);
    output << "Найдено: " << foundIds.size() << " | После фильтра: " << filtered.size()
           << " | Оценка: " << score << " | Тегов в реестре: " << tagRegistry_.countTags() << "\n";
}

void ConsoleMenu::handleNotificationsAndReminders(std::istream& input, std::ostream& output) {
    std::string docId;
    output << "Введите ID документа для рассылки уведомлений: ";
    input >> docId;
    Document doc = system_.getStoredDocument(docId);
    Subscription sub(defaultUser_.getUserId(), docId, true);
    notificationService_.addSubscription(sub);
    std::size_t sent = notificationService_.notifySubscribers(doc, "Document event");
    Notification directNote("NTF-DIRECT", defaultUser_.getUserId(), "Direct notice", false);
    directNote.markAsRead();
    Reminder reminder("REM-1", docId, defaultUser_.getUserId(), kDefaultReminderHour);
    reminder.reschedule(kRescheduledReminderHour);
    std::size_t unread = notificationService_.countUnreadForUser(defaultUser_);
    output << "Отправлено: " << sent << " | Непрочитанных: " << unread
           << " | Напоминание перенесено на: " << reminder.getDueHour() << ":00\n";
}

void ConsoleMenu::handleAuditAndCompliance(std::istream& input, std::ostream& output) {
    std::string docId;
    output << "Введите ID документа для проверки комплаенса: ";
    input >> docId;
    Document doc = system_.getStoredDocument(docId);
    AuditEntry manualEntry("AUD-1", defaultUser_.getUserId(), docId, "CHECK_COMPLIANCE");
    std::string logLine = manualEntry.formatLogLine();
    SecurityIncident incident("INC-1", defaultUser_.getUserId(), kHighSeverityScore, false);
    incident.resolveIncident();
    complianceChecker_.registerIncident(incident);
    complianceChecker_.verifyDocumentCompliance(doc, signatureService_);
    output << "Комплаенс успешно пройден (" << logLine
           << ") | Инцидентов ИБ: " << complianceChecker_.countIncidents() << "\n";
}

void ConsoleMenu::handleAnalyticsAndStatus(std::istream& input, std::ostream& output) {
    std::string docId;
    output << "Введите ID документа для отчёта и проверки SLA: ";
    input >> docId;
    Document doc = system_.getStoredDocument(docId);
    workflowMetrics_.recordCompletion(kDefaultProcessingHours, true);
    WorkflowState state(docId, doc.getStatus(), kDefaultProcessingHours, false);
    slaMonitor_.checkWorkflowSla(state);
    AnalyticsReporter reporter("DocFlowSummary", true);
    std::string metricsSummary = reporter.buildMetricsSummary(workflowMetrics_);
    std::string deptSummary = reporter.buildDepartmentSummary(defaultDepartment_, departmentStats_);
    output << "Документ: " << doc.getTitle() << " | Статус: " << doc.getStatus()
           << " | Подписей: " << signatureService_.countSignatures(docId)
           << " | Записей аудита: " << system_.getAuditCount() << "\n"
           << metricsSummary << " | " << deptSummary << "\n";
}

void ConsoleMenu::executeDocumentAndWorkflowCommand(
    int choice, std::istream& input, std::ostream& output) {
    switch (choice) {
        case 1: handleCreateDocument(input, output); break;
        case 2: handleTemplateAndAccess(input, output); break;
        case 3: handleSpecializedDocuments(input, output); break;
        case 4: handleWorkflowAndApproval(input, output); break;
        case 5: handleSignAndStamp(input, output); break;
        default: output << "Неизвестная команда.\n"; break;
    }
}

void ConsoleMenu::executeInfrastructureCommand(
    int choice, std::istream& input, std::ostream& output) {
    switch (choice) {
        case 6: handleStorageAndArchive(input, output); break;
        case 7: handleSearchAndSort(input, output); break;
        case 8: handleNotificationsAndReminders(input, output); break;
        case 9: handleAuditAndCompliance(input, output); break;
        case 10: handleAnalyticsAndStatus(input, output); break;
        default: output << "Неизвестная команда.\n"; break;
    }
}

void ConsoleMenu::dispatchChoice(int choice, std::istream& input, std::ostream& output) {
    if (choice >= 1 && choice <= 5) {
        executeDocumentAndWorkflowCommand(choice, input, output);
    } else {
        executeInfrastructureCommand(choice, input, output);
    }
}

void ConsoleMenu::runInteractiveLoop(std::istream& input, std::ostream& output) {
    int choice = -1;
    while (choice != 0) {
        printMenu(output);
        if (!(input >> choice) || choice == 0) {
            break;
        }
        try {
            dispatchChoice(choice, input, output);
        } catch (const DocumentWorkflowException& ex) {
            output << "[Ошибка " << ex.getErrorCode() << "]: " << ex.what() << "\n";
        }
    }
}

}
