/*
 * This file contains code from "C++ Primer, Fifth Edition", by Stanley B.
 * Lippman, Josee Lajoie, and Barbara E. Moo, and is covered under the
 * copyright and warranty notices given in that book:
 * 
 * "Copyright (c) 2013 by Objectwrite, Inc., Josee Lajoie, and Barbara E. Moo."
 * 
 * 
 * "The authors and publisher have taken care in the preparation of this book,
 * but make no expressed or implied warranty of any kind and assume no
 * responsibility for errors or omissions. No liability is assumed for
 * incidental or consequential damages in connection with or arising out of the
 * use of the information or programs contained herein."
 * 
 * Permission is granted for this code to be used for educational purposes in
 * association with the book, given proper citation if and when posted or
 * reproduced.Any commercial use of this code requires the explicit written
 * permission of the publisher, Addison-Wesley Professional, a division of
 * Pearson Education, Inc. Send your request for permission, stating clearly
 * what code you would like to use, and in what specific way, to the following
 * address: 
 * 
 * 	Pearson Education, Inc.
 * 	Rights and Permissions Department
 * 	One Lake Street
 * 	Upper Saddle River, NJ  07458
 * 	Fax: (201) 236-3290
*/ 

#ifndef SALES_DATA_H
#define SALES_DATA_H

#include <string>

class Sales_data {
public:
	Sales_data():units_sold_(0), revenue_(0){};
	Sales_data(std::istream& is){
		read(is);
	}
	std::string isbn() const{
		return bookNo_;
	}//这个const是把this指针声明成const Sales_data* const（原本为Sales_data* const，即指向普通对象的常量指针），如果不这样声明，常量对象指针无法赋给this指针，该成员函数无法被常量对象调用。这个const还可以告诉程序员：这个函数不改变对象内部任何东西
	unsigned numUnitsSold() const{
		return units_sold_;
	}
	Sales_data& combine(const Sales_data& rhs){
		units_sold_ += rhs.units_sold_;
		revenue_ += rhs.revenue_;
		return *this;
	}
	double getRevenue() const {
		return revenue_;
	}
	double avg_price(){
		if(units_sold_)return revenue_/units_sold_;
		else return 0;
	};
	std::istream& read(std::istream& is){
		double price = 0;
		is >> bookNo_ >> units_sold_ >> price;
		revenue_ = price * units_sold_;
		return is;
	}
private:
	std::string bookNo_;
	unsigned units_sold_;
	double revenue_;
};

Sales_data add(const Sales_data& lhs, const Sales_data& rhs){
	Sales_data sum = lhs;
	return sum.combine(rhs);
}

std::ostream& print(std::ostream& os, const Sales_data& item){
	os << item.isbn() << " " << item.numUnitsSold() << " " << item.getRevenue();
	return os;
}


#endif
