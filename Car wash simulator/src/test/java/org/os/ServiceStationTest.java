package org.os;

import org.junit.jupiter.api.Test;

import java.time.Duration;

import static org.junit.jupiter.api.Assertions.assertTimeoutPreemptively;

class ServiceStationTest {
    @Test
    void builtInTestOptionRunsWithoutInteractiveInput() {
        assertTimeoutPreemptively(Duration.ofSeconds(15), () -> ServiceStation.main(new String[]{"--test"}));
    }
}
