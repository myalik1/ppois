#include <gtest/gtest.h>
#include "../../include/security/SecurityIncident.h"
#include "../../include/exceptions/AirportExceptions.h"

using namespace airport;

TEST(SecurityIncidentTest, EscalateAndResolveIncident) {
    SecurityBadge officer("SEC-1", "Guard", 2, true);
    SecurityBadge supervisor("SEC-9", "Chief", 5, true);
    SecurityCheckpoint cp("CP-1", "Zone-A", true);
    SecurityIncident incident("INC-01", "Unattended bag", 3, officer);

    EXPECT_FALSE(incident.isHighSeverity());
    incident.escalateIncident(cp);
    EXPECT_TRUE(incident.isHighSeverity());
    EXPECT_TRUE(cp.getIsLockdownActive());

    EXPECT_THROW(incident.resolveIncident(cp, officer), SecurityBreachException);
    EXPECT_NO_THROW(incident.resolveIncident(cp, supervisor));
    EXPECT_TRUE(incident.getIsResolved());
    EXPECT_FALSE(cp.getIsLockdownActive());
    EXPECT_EQ(incident.getIncidentId(), "INC-01");
    EXPECT_EQ(incident.getDescription(), "Unattended bag");
    EXPECT_EQ(incident.getSeverityLevel(), 4);
    EXPECT_EQ(incident.getReportingBadgeId(), "SEC-1");
}
