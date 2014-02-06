#include <gtest/gtest.h>
#include <stdexcept>
#include <sstream>
#include "LongInt.hpp"
#include "Vector.hpp"


#define LENGTH1 20
#define VAL1 0xFF
TEST(Vector, Construct) {
	size_t size;
	Vector vector(LENGTH1, VAL1);
	ASSERT_TRUE(vector.size() == LENGTH1);
	for (size_t i = 0; i < LENGTH1; i++) {
		ASSERT_TRUE(vector[i] == VAL1);
	}
}

#define LENGTH2 50
#define VAL2 0xFA
#define ADDITIONAL_LENGTH 11
TEST(Vector, Enlarge) {
	Vector vector(LENGTH2, VAL2);
	ASSERT_TRUE(vector.size() == LENGTH2);
	vector.resize(LENGTH2 - 5);
	ASSERT_TRUE(vector.size() == LENGTH2);
	vector.resize(LENGTH2 + ADDITIONAL_LENGTH);
	ASSERT_TRUE(vector.size() == LENGTH2 + ADDITIONAL_LENGTH);
	for (size_t i = 0; i < LENGTH2; i++) {
		ASSERT_TRUE(vector[i] == VAL2);
	}
	for (size_t i = LENGTH2; i < LENGTH2 + ADDITIONAL_LENGTH; i++) {
		ASSERT_TRUE(vector[i] == 0);
	}
}

TEST(LongInt, Consturct) {
	std::string number1("13ojp4f12");
	ASSERT_THROW(LongInt long_int(number1), std::invalid_argument);
	number1 = "0x098dcadcCDA23e4462384";
	EXPECT_NO_THROW({
		LongInt long_int(number1);
	});
	number1 = "39264519341648163294462384";
	EXPECT_NO_THROW({
		LongInt long_int(number1);
	});
	EXPECT_NO_THROW({
		LongInt long_int("11");
	});
	EXPECT_NO_THROW({
		LongInt long_int("72");
	});
}

TEST(LongInt, CreateNDump) {
	std::string str1("134372423648234128739264519341648163294462384");
	LongInt number1(str1);
	std::stringstream ss;
	ss<<number1;
	ASSERT_TRUE(ss.str() == str1);
}

TEST(LongInt, Plus) {
	std::stringstream ss1, ss2;
	LongInt long_int("1542");
	long_int+=LongInt("15");
	ss1<<LongInt("0xAC685DE30B1782") + LongInt("0xFE84CB243163E97C4D512");
	ASSERT_TRUE(ss1.str() == "19230891164458265961557140");
	ss2<<long_int;
	ASSERT_TRUE(ss2.str() == "1557");
}

TEST(LongInt, Multiply) {
	std::stringstream ss;
	LongInt long_int("15");
	long_int *= "2";
	ss<<long_int;
	ASSERT_TRUE(ss.str() == "30");
	ss.clear();	ss.str("");
	ss<<LongInt("15") * LongInt("18");
	ASSERT_TRUE(ss.str() == "270");
	ss.clear();	ss.str("");
	ss<<LongInt("0x574a10123") * LongInt("0x1234DB14AF2");
	ASSERT_TRUE(ss.str() == "29316118711127661752598");
	ss.clear();	ss.str("");
	ss<<LongInt("0xAC685DE30B1782") * LongInt("0xFE84CB243163E97C4D51");
	ASSERT_TRUE(ss.str() == "58327831753986849041238136227011847031330");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
