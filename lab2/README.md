# Лабораторная работа №2. Документооборот

## Описание классов предметной области

Формат строки: `Класс | число полей | число методов | связанные классы`.

| Класс | Поля | Методы | Ассоциации (связанные классы) |
|---|---|---|---|
| Permission | 3 | 2 | — |
| Role | 3 | 3 | Permission |
| Department | 4 | 2 | — |
| User | 5 | 3 | Department |
| AccessController | 3 | 3 | User, Role, Permission |
| Tag | 3 | 2 | — |
| Attachment | 4 | 2 | — |
| DocumentMetadata | 4 | 2 | — |
| DocumentVersion | 4 | 2 | — |
| Document | 8 | 4 | DocumentMetadata, DocumentVersion, Attachment, Tag |
| DocumentTemplate | 4 | 2 | Document, User |
| ContractDocument | 4 | 2 | Document |
| InvoiceDocument | 4 | 2 | Document |
| OrderDocument | 4 | 2 | Document, Department |
| ReportDocument | 4 | 2 | Document, User |
| MemoDocument | 4 | 2 | Document, User |
| ApprovalStep | 4 | 2 | User |
| EscalationRule | 3 | 2 | — |
| ApprovalRoute | 3 | 3 | ApprovalStep |
| WorkflowState | 4 | 2 | — |
| WorkflowManager | 3 | 3 | Document, ApprovalRoute, WorkflowState, User, EscalationRule |
| CryptoHasher | 3 | 2 | — |
| Certificate | 5 | 2 | User |
| DigitalSignature | 4 | 2 | Document |
| OfficialStamp | 3 | 2 | — |
| SignatureService | 3 | 3 | CryptoHasher, Document, User, Certificate, DigitalSignature |
| StorageLocation | 4 | 2 | — |
| Folder | 3 | 2 | Document |
| ArchivePolicy | 3 | 2 | — |
| ArchiveRecord | 4 | 2 | ArchivePolicy |
| DocumentRepository | 3 | 3 | StorageLocation, Document |
| BackupManager | 3 | 2 | DocumentRepository |
| SearchFilter | 3 | 2 | Document |
| IndexEntry | 3 | 2 | — |
| TagRegistry | 3 | 2 | Tag |
| DocumentSorter | 2 | 2 | Document |
| SearchEngine | 3 | 3 | Document, IndexEntry, SearchFilter |
| NotificationChannel | 3 | 2 | — |
| Notification | 4 | 2 | User |
| Subscription | 3 | 2 | Document |
| Reminder | 4 | 2 | — |
| NotificationService | 3 | 3 | NotificationChannel, Notification, Subscription, Document, User |
| AuditEntry | 4 | 2 | Document |
| AuditLogger | 3 | 3 | AuditEntry, User, Document |
| ComplianceRule | 3 | 2 | Document |
| SecurityIncident | 4 | 2 | — |
| ComplianceChecker | 3 | 3 | ComplianceRule, SecurityIncident, Document, SignatureService |
| WorkflowMetrics | 3 | 2 | — |
| DepartmentStats | 3 | 2 | — |
| SlaMonitor | 3 | 2 | WorkflowState |
| AnalyticsReporter | 2 | 2 | WorkflowMetrics, Department, DepartmentStats |
| DocumentFlowSystem | 5 | 3 | AccessController, DocumentRepository, WorkflowManager, AuditLogger, User, Document, ApprovalRoute |

### Исключения (12)

- DocumentWorkflowException
- InvalidDocumentStateException
- UnauthorizedAccessException
- DocumentNotFoundException
- SignatureVerificationException
- CertificateExpiredException
- WorkflowRouteException
- StorageCapacityExceededException
- ArchivePolicyViolationException
- InvalidDocumentDataException
- ComplianceViolationException
- SlaBreachException

### Итоговая статистика

| Показатель | Значение |
|---|---|
| Классы | 52 |
| Поля | 184 |
| Поведения | 118 |
| Ассоциации | 71 |
| Исключения | 12 |
