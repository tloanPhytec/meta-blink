SUMMARY = "Example Systemd Service Recipe"
DESCRIPTION = "Blink Recipe for the Cafe Yocto Series"
LICENSE = "CLOSED"

inherit systemd

SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE_${PN} = "blink.service"

SRC_URI_append = " 		\
	file://blink.c 		\
	file://blink.service 	\
"

FILES_${PN} += "				\
	${systemd_unitdir}/system/blink.service \
	${bindir}/blink				\
"

do_compile() {
         ${CC} ${WORKDIR}/blink.c -o ${WORKDIR}/blink
}

do_install_append() {
  install -d ${D}/${systemd_unitdir}/system
  install -m 0644 ${WORKDIR}/blink.service ${D}/${systemd_unitdir}/system

  install -d ${D}/${bindir}
  install -m 0755 ${WORKDIR}/blink ${D}/${bindir}
}

RDEPENDS_${PN} += "bash"

COMPATIBLE_MACHINE = "phyboard-electra-am64xx-1"
