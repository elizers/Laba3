#pragma once
#include <string>
#include "Date.h"
#include "Utils.h"

class AccountStructure			// ��������� �����
{
private:
	std::string _name_of_firm;  // �������� �����
	std::string _type_of_work;  // ��� �����
	std::string _unit;		    // ������� ���������
	int _cost_per_unit;		    // ��������� ������� ����������� ������
	Date _date_of_execution;	// ���� ����������
    float _scope_of_work;       // ����� �����

public:
	AccountStructure();
	AccountStructure(std::string name_of_firm, std::string type_of_work, std::string unit, int cost_per_unit, Date date_of_execution, float scope_of_work);

	std::string get_name_of_firm() const;
	std::string get_type_of_work() const;
	std::string get_unit() const;
	int get_cost_per_unit() const;
	Date get_date_of_execution() const;
	float get_scope_of_work() const;

	void set_name_of_firm(const std::string& name);
	void set_type_of_work(const std::string& type);
	void set_unit(const std::string& unit);
	void set_cost_per_unit(const int cost);
	void set_date_of_execution(const Date& date);
	void set_scope_of_work(const float scope);

	friend std::ostream& operator<< (std::ostream& out, const AccountStructure& record);
	friend std::istream& operator>> (std::istream& in, AccountStructure& record);
	friend AccountStructure add(AccountStructure& record);

	friend bool operator== (const AccountStructure& rec1, const AccountStructure& rec2);
	friend bool operator!= (const AccountStructure& rec1, const AccountStructure& rec2);
	friend bool compare(const AccountStructure& r1, const AccountStructure& r2);
};