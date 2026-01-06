all:
	$(MAKE) -C server
	$(MAKE) -C client_gui

clean:
	$(MAKE) -C server clean
	$(MAKE) -C client_gui clean
