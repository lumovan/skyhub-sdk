.PHONY: all clean debug init prepare release

all:
	@./scripts/build-arm.sh --clean

prepare:
	@./scripts/download-libs.sh

clean:
	@rm -fv ./scripts/libpayload-example.so
