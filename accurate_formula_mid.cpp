//#include "accurate_formula.h"
//#include "base/base_paths.h"
//#include "base/path_service.h"
//#include "base/files/file_path.h"
//#include "base/files/file_util.h"
#include "opencv2/core.hpp"
#include "merge_model.h"
#include "rec_formula_recognization.hpp"
#include <string>
#include <vector>
#include"json/json.h"

using namespace facethink; //algorithm namespace

/**
 * 此处对HandleRequest包装一层的目的：防止当前HandleRequest不能很好的
 * 满足后续的需求；若能满足，也可以直接在service_main.cpp的Listen中直
 * 接调用HandleRequest方法
 */
merge_model m_merge_model_;
std::string encoder_model_path1_;
std::string encoder_model_path2_;

std::string decoder_model_path1_;
std::string decoder_model_path2_;

std::string config_path1_;
std::string config_path2_;

std::string word_dict_path1_;
std::string word_dict_path2_;
std::unique_ptr<RecFormulaRecognization> p_detector1_ = nullptr;
std::unique_ptr<RecFormulaRecognization> p_detector2_ = nullptr;



bool Init() {
	encoder_model_path1_ = "./formula/model/optimized_batch6_rec_formula_recognization_encoder_v1.0.1.pt";
	encoder_model_path2_ = "./formula/model/optimized_batch6_rec_formula_recognization_encoder_v1.0.2.pt";

	decoder_model_path1_ = "./formula/model/optimized_batch6_rec_formula_recognization_decoder_v1.0.1.pt";
	decoder_model_path2_ = "./formula/model/optimized_batch6_rec_formula_recognization_decoder_v1.0.2.pt";

	config_path1_        = "./formula/model/config_v1.0.1.ini";
	config_path2_        = "./formula/model/config_v1.0.2.ini";

	word_dict_path1_     = "./formula/model/rec_formula_recognization_words_v1.0.1.txt";
	word_dict_path2_     = "./formula/model/rec_formula_recognization_words_v1.0.2.txt";

	// init algorithm model
	if (nullptr == p_detector1_) {
		p_detector1_.reset(RecFormulaRecognization::create(encoder_model_path1_,
					decoder_model_path1_,
					config_path1_,
					word_dict_path1_));
	}
	if (nullptr == p_detector2_) {
        p_detector2_.reset(RecFormulaRecognization::create(encoder_model_path2_,
                                                        decoder_model_path2_,
                                                        config_path2_,
                                                        word_dict_path2_));
    }

	return true;
}

std::vector<regData> ModelFunc(const cv::Mat &cv_image, RecFormulaRecognization* detector)
{
	std::vector<regData> reg_data;
	std::vector<float> formula_pro;
	std::vector<std::string> formula_result;
	int ret = detector->detect(cv_image, formula_result, formula_pro);
	if (0 != ret)
		return reg_data;

	for (int i = 0; i < formula_pro.size(); ++i) {
		regData data;
		data.prob = formula_pro[i];
		data.reg  = formula_result[i];
		reg_data.emplace_back(data);
	}
	return reg_data;
}
int main(){
	if(!Init()){
		std::cout<<"Init Error"<<endl;
		return 0;
	}
	std::vector<regData> result1;
	std::vector<regData> result2;
	std::vector<regData> result3;
	std::vector<int>mulFlagVec;
	std::vector<regData> lastPre;

	cv::Mat image = cv::imread("./image.png");

	result1 = ModelFunc(image,p_detector1_.get());
	result2 = ModelFunc(image,p_detector2_.get());

	m_merge_model_.merge_resultBatch(result1,result2,result3,mulFlagVec,lastPre);
	Json::Value datas;
	for(auto & reg : lastPre){
		Json::Value json_data;
		json_data["reg_prob"] = reg.prob;
		json_data["formula_result"] = reg.reg;
		datas["data"].append(json_data);
	}
	std::cout<<datas<<std::endl;


	
	return 0;

}

