all: creeper taproot

creeper:
	mkdir -p src/creeper/build
	cd src/creeper && make upload

taproot:
	mkdir -p src/taproot/build
	cd src/taproot && make upload
