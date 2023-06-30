#include<iostream>
#include<vector>
#include<string>
#include <numeric>
#include<algorithm>
using namespace std;


struct regData
{
        std::string reg;
        float prob;
};

class merge_model
{
private:
	int countNum(const string T, const string P);
	bool isMulty(regData &selectReg);
	void Join(const std::vector<std::string>::iterator& begin, const std::vector<std::string>::iterator& end, std::string& r, const std::string& s);
	void removeBlank(string &input);
	void SplitString(const string& s, vector<string>& v, const string& c);

	std::vector<std::string> SplitCorChinese(const std::string &str, const std::string &pattern);
	std::string ReplaceAll(const std::string& s, const std::string& from, const std::string& to);	
	std::string leftright(string input);
	std::string alinge(string input);
	std::string kuohao(std::string input);
	std::string balence(std::string input);
        void normalReplace(string& str, const string& old_value, const string& new_value);
	int mulPostProcess(regData &selectReg);
	int singlePostProcess(regData &selectReg);
	int merge2Model(const vector<string> regOrderResV, const vector<float> regOrderProbV, regData &selectReg);
	int merge3Model(const vector<string> regOrderResV, const vector<float> regOrderProbV, regData &selectReg);

public:
	int merge_resultBatch( vector<regData> resModelBatch_1,vector<regData> resModelBatch_2, vector<regData> &resModelBatch_3, vector<int> &mulFlagVec, vector<regData> &last_pre);
	int merge_result(const vector<regData> regResult, regData &selectReg);
};
