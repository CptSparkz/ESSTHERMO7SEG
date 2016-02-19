# invoke SourceDir generated makefile for application.pem4f
application.pem4f: .libraries,application.pem4f
.libraries,application.pem4f: package/cfg/application_pem4f.xdl
	$(MAKE) -f C:\Users\Fsham\Desktop\7seg_output\connected_launchpad_rtos_raw/src/makefile.libs

clean::
	$(MAKE) -f C:\Users\Fsham\Desktop\7seg_output\connected_launchpad_rtos_raw/src/makefile.libs clean

