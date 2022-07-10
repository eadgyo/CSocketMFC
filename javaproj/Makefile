JAVA_HOME = /usr/lib/jvm/java-17-openjdk

CXX= gcc
LDFLAGS=../libCSocketMFC.so

CXXFLAGS += -Wall
CXXFLAGS += -I. -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I../include

.PHONY: all
all: libcasyncsocket_jni.so MainJNI.class

clean:
	rm JNICAsyncSocket.class JNICAsyncSocket.h libcasyncsocket_jni.so 

libcasyncsocket_jni.o: JNICAsyncSocket.h libcasyncsocket_jni.cpp 
libcasyncsocket_jni.so:  libcasyncsocket_jni.o
JNICAsyncSocket.h: JNICAsyncSocket.class
JNICAsyncSocket.class: JNICAsyncSocket.java
MainJNI.class : MainJNI.java

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -fPIC -c $< 

%.so: %.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -shared -o $@ $<

%.class: %.java
	javac $<

%.h: %.class
	javah -cp . $(<:.class=)



