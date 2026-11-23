#include <unity.h>
#include "services/TransportPolicy.h"
using namespace paperos;
void setUp() {} void tearDown() {}
void test_only_https_urls_are_allowed() {
    TEST_ASSERT_TRUE(isSecureUrl("https://home.example/api"));
    TEST_ASSERT_FALSE(isSecureUrl("http://home.example/api"));
    TEST_ASSERT_FALSE(isSecureUrl("https://"));
    TEST_ASSERT_FALSE(isSecureUrl("ftp://home.example"));
}
void test_certificate_markers_in_order() {
    TEST_ASSERT_TRUE(hasPemCertificate("-----BEGIN CERTIFICATE-----\nabc\n-----END CERTIFICATE-----\n"));
    TEST_ASSERT_FALSE(hasPemCertificate("-----END CERTIFICATE-----\n-----BEGIN CERTIFICATE-----"));
    TEST_ASSERT_FALSE(hasPemCertificate(""));
}
int main() {
    UNITY_BEGIN();
    RUN_TEST(test_only_https_urls_are_allowed);
    RUN_TEST(test_certificate_markers_in_order);
    return UNITY_END();
}
