OBJS = BigNumber.o BigRational.o BigInteger.o main.o
CXX = g++
TARGET = pa3

$(TARGET): $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS)

all: $(TARGET)

main.o: main.cpp BigInteger.h BigRational.h BigNumber.h
	$(CXX) -c main.cpp

BigNumber.o: BigNumber.cpp BigNumber.h
	$(CXX) -c BigNumber.cpp

BigRational.o: BigRational.cpp BigRational.h BigNumber.h
	$(CXX) -c BigRational.cpp

BigInteger.o: BigInteger.cpp BigInteger.h BigRational.h
	$(CXX) -c BigInteger.cpp

clean:
	rm ${OBJX} $(TARGET) 

