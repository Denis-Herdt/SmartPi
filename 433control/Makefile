all: RFSniffer sniff

sniff: RCSwitch.o sniff.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi

RFSniffer: RCSwitch.o RFSniffer.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -lwiringPi

irreceive: irreceive.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $+ -o $@ -llirc_client	

clean:
	$(RM) *.o sniff servo RFSniffer irrecord
