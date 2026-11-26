/* Test-only RSA-2048 key and self-signed certificate (CN=magma-harness,
 * serial 1, valid for 100 years) used as the TLS server identity and as the
 * PKCS#7 recipient. Generated with:
 *   openssl genrsa -out rsa.pem 2048
 *   openssl req -new -x509 -key rsa.pem -days 36500 -subj /CN=magma-harness \
 *       -set_serial 1 -out rsa.crt
 * pocs/gen_tls.c links against the same material, so regenerating these
 * requires regenerating the TLS PoCs. */

#ifndef OPENSSL_HANDWRITTEN_KEYS_H
#define OPENSSL_HANDWRITTEN_KEYS_H

static const char harness_key_pem[] =
  "-----BEGIN PRIVATE KEY-----\n"
  "MIIEvgIBADANBgkqhkiG9w0BAQEFAASCBKgwggSkAgEAAoIBAQC5iIyhzf7bJGNb\n"
  "WMwuyxtDMskSLsgzTWsKR1XMJD67WhBX1U6SWB3Tq6mleGAB9zlMm2LsSx8vLRqo\n"
  "JVbARn6f871bhSBrvJcMT3vvY/AuAQA3awcCAlBa5LBKmU9Wbo0x16bvQNN/JFG6\n"
  "xwV7leStZ0KOFMuF1Pnelmlup/idvCIzxq00Lk9pzf3DBnWzZ4pJtPpMHjE3iZCb\n"
  "gOjODzotyfERnrxFjdzoe/iPukuoAPqG1TTjGJBoa7d0HcaF6hXkKkdPGe/u80nh\n"
  "oEw24o6gYJx7/FCZTZa12eSUWJyqSBkNQWr42A53FSGLIszrDb3EbUSOeDoaVOvi\n"
  "/YiZBHbxAgMBAAECggEAI1BERD/rNFbWunpKUtXB2KZ/8wAIhwtDRm+RewujDRH1\n"
  "bmJhVCWFd9aCscYZsAYYV+Zzi7o4s0gIfNyuiGZij5ta/WJ3a0o4DdXLJyOEgZ0b\n"
  "J3EtokpCdSp2C5zmpvLf2Q7M7VkPaHHHRJ/BAWbkYcT3vAdlPZHuBVnns3IxNgRX\n"
  "drRLdIEOg2iLVcc1XoEX4OTEPyPkJ3L95RKwmSoZUgFEbjphKhjWI4mnTeHCu2oD\n"
  "uEa2tlkKR+acQz8gpjXEj3hUyFv8CWxlhDSFerLbBkY0o6L3USMVqkVOX0zF+498\n"
  "eSliiEfnL0J3AIzTv3eAt36Wi7sJMLM9IjJfve4dKQKBgQD3NPWUb6BSNjHVfj10\n"
  "BqiKczIITGzMpReRSGJxR8sYLqtv/8IS/EoyNj1jANFymUn0dhMEZjMfiyfkhvUF\n"
  "pfSzMcWCFZwM5bX5mcDHeeFc26BUofNrnS3PueIKOuVcJkh7Ly4kZ8n04wrjEfjf\n"
  "cQgbICHiTZBa6vDD2kS5CoDHpwKBgQDAIf9khWqWSpLdpD7dhQu0j5znVDPZe5m+\n"
  "JK9IHrxDPb4J4mWZ4meTnv+ac8G4Eu1isuuAdqmVdR1R7HlT3zYOpszwOdhswWa1\n"
  "hwAIbYiw3ObNtDLySAzBvmFTi0F6jANkZAJfCVmiZlKaBlKD8WW4AYXU4wCk8niZ\n"
  "s0aKrSMfpwKBgQDGGkue+2Fn4IRJCVRn8ZoI8U2r9srNqJNdWruA+j6YD3ZVV4kI\n"
  "O+Odn3fMKfCuvIbWf/S3dssLQTHj4f7i2t5g58bWe0jF0SPmdT9W26YtCtfOWsY+\n"
  "fAQlTloFRrNdCFTXWrTIeeAO/g9QbquZK/SKAFMHDo9bPKFa4kRmYTNYSwKBgBQ4\n"
  "/9qiuE9NVhwCF6PVRyAgJZGrqTFw8wOydMiQg5xIOWJs8+i4jdJZ3+lv2an4RAgp\n"
  "cOQ6mSrkAswGqdaMHfJ42AVI8WCxEpB0vyoj7UlAVwK7vskFkGIsGa5jb+boKcs9\n"
  "Q4qhP0/6mSMhGzpMBDrT3jREGGNEKjFzTy91fcbtAoGBAIj+Jw2THBtLRccbidOb\n"
  "A49TUI81oJhrN6UCb1Mj0+AlqVlt6EJ+fXSMPbPxwuLMk7sdBLNpz4CLwd1O1GVh\n"
  "7qrxlSVqpf0NHF2uXhwcLGuV5cc4RbsoHfjHA+S4TnUxykaAvHWdyJAQl13FzCzq\n"
  "7WGl9IgperyNYwZ/SM+5wsLB\n"
  "-----END PRIVATE KEY-----\n";

static const char harness_cert_pem[] =
  "-----BEGIN CERTIFICATE-----\n"
  "MIIDADCCAeigAwIBAgIBATANBgkqhkiG9w0BAQsFADAYMRYwFAYDVQQDDA1tYWdt\n"
  "YS1oYXJuZXNzMCAXDTI2MTEyNjAxNTgxMFoYDzIxMjYxMTAyMDE1ODEwWjAYMRYw\n"
  "FAYDVQQDDA1tYWdtYS1oYXJuZXNzMIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIB\n"
  "CgKCAQEAuYiMoc3+2yRjW1jMLssbQzLJEi7IM01rCkdVzCQ+u1oQV9VOklgd06up\n"
  "pXhgAfc5TJti7EsfLy0aqCVWwEZ+n/O9W4Uga7yXDE9772PwLgEAN2sHAgJQWuSw\n"
  "SplPVm6NMdem70DTfyRRuscFe5XkrWdCjhTLhdT53pZpbqf4nbwiM8atNC5Pac39\n"
  "wwZ1s2eKSbT6TB4xN4mQm4Dozg86LcnxEZ68RY3c6Hv4j7pLqAD6htU04xiQaGu3\n"
  "dB3GheoV5CpHTxnv7vNJ4aBMNuKOoGCce/xQmU2WtdnklFicqkgZDUFq+NgOdxUh\n"
  "iyLM6w29xG1Ejng6GlTr4v2ImQR28QIDAQABo1MwUTAdBgNVHQ4EFgQU9TlyPumu\n"
  "JCmnPf3T0ucBPJ+odS8wHwYDVR0jBBgwFoAU9TlyPumuJCmnPf3T0ucBPJ+odS8w\n"
  "DwYDVR0TAQH/BAUwAwEB/zANBgkqhkiG9w0BAQsFAAOCAQEAQ9wxcb5RUNHyQgtY\n"
  "27rUWxWUw+qIQBunshTk9hCBBK2ageWXd6kES2bm/5eecxrH7Qmh1A2ZdHpiVQ8d\n"
  "u09obfcBhWwPCg9Y8pyuZjp9CAAQXFALvXmBJKwi7QB0zu+imGfiKSEOUs1PhcuC\n"
  "zKfRVpGEYQiYwNnwWiK5n6CDsk3/eRgg/Y/F4XL/JnRleBFEVrQjD9hUcZ8zKEw1\n"
  "bPuunSPaRZX45kuJY56Fzi6gg7YxOdb3loAW+NDWvpW/z0AHA61em7vaS0WdT/Ov\n"
  "QZlARz9XFbU2i2Mh4uAZqLN0cB3olelSMKol3X8bRktY/t3eeZXLbHepvTXPBzvs\n"
  "EIulBg==\n"
  "-----END CERTIFICATE-----\n";

#endif /* OPENSSL_HANDWRITTEN_KEYS_H */
