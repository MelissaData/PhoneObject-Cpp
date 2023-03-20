# Melissa Phone Object Windows C++

CXX=cl
CXXFLAGS=-Zi -EHsc
LDLIBS=mdPhone.lib
RM=del /q /f

all: MelissaPhoneObjectWindowsCpp.exe clean

MelissaPhoneObjectWindowsCpp.exe:	Main.cpp mdPhone.h mdEnums.h
	$(CXX) $(CXXFLAGS) Main.cpp PhoneObject.cpp $(LDLIBS) /Fe:.\Build\MelissaPhoneObjectWindowsCpp.exe

clean:
	$(RM) *.obj *.ilk *.pdb *.h.hash *.lib.hash 

