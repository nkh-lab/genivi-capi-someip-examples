# Add to /device/linaro/hikey/hikey960/device-hikey960.mk:
# $(call inherit-product-if-exists, vendor/genivi-capi-someip-examples/aosp/config.mk)

PRODUCT_PACKAGES += Interface1-Service
PRODUCT_PACKAGES += Interface1-Client

BOARD_SEPOLICY_DIRS += vendor/genivi-capi-someip-examples/aosp/sepolicy
