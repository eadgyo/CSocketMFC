JAVA_HOME = /usr/lib/jvm/java-8-openjdk

CXX= gcc
LDFLAGS=../libCSocketMFC.so

CXXFLAGS += -Wall
CXXFLAGS += -I. -I$(JAVA_HOME)/include -I$(JAVA_HOME)/include/linux -I../include

.PHONY: all
all: libcasyncsocket_jni.so MainJNI.class

all2: helper.so 

all3: libDLL_TIM_JNI.so helper.so 

clean:
	rm JNICAsyncSocket.class JNICAsyncSocket.h libcasyncsocket_jni.so 

helper.so: helper.o
helper.o: helper.h
libDLL_TIM_JNI.o: JNITest.h JNITest.cpp
libDLL_TIM_JNI.so: libDLL_TIM_JNI.o

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



