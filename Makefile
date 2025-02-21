SLOPCHATSERVER_DIR=slopchat-server
SLOPCHATCLIENT_DIR=slopchat-client
LIBSLOPCHAT_DIR=libslopchat

all: libslopchat.so slopchatd slopchatx

dev: libslopchat-dev slopchat-server-dev slopchat-client-dev

slopchatd:
	$(MAKE) -C $(SLOPCHATSERVER_DIR)

slopchatx:
	$(MAKE) -C $(SLOPCHATCLIENT_DIR)

libslopchat.so:
	$(MAKE) -C $(LIBSLOPCHAT_DIR)

docs:
	doxygen

slopchatx-appimage:
	./packaging/make-appimage.sh slopchat-client libslopchat assets

.PHONY: slopchat-server-dev
slopchat-server-dev:
	$(MAKE) -C $(SLOPCHATSERVER_DIR) dev

.PHONY: slopchat-client-dev
slopchat-client-dev:
	$(MAKE) -C $(SLOPCHATCLIENT_DIR) dev

.PHONY: libslopchat-dev
libslopchat-dev:
	$(MAKE) -C $(LIBSLOPCHAT_DIR) dev

.PHONY: clean
clean:
	$(MAKE) -C $(SLOPCHATSERVER_DIR) clean
	$(MAKE) -C $(SLOPCHATCLIENT_DIR) clean
	$(MAKE) -C $(LIBSLOPCHAT_DIR) clean
