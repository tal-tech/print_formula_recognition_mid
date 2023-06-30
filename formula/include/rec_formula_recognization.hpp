#ifndef __FACETHINK_API_REG_FORMULA_RECOGNIZATION_HPP__
#define __FACETHINK_API_REG_FORMULA_RECOGNIZATION_HPP__

#include <string>
#include <opencv2/opencv.hpp>
#ifdef WIN32
#ifdef DLL_EXPORTS
#define EXPORT_CLASS   __declspec(dllexport)
#define EXPORT_API  extern "C" __declspec(dllexport)
#define EXPORT_CLASS_API
#else
#define EXPORT_CLASS   __declspec(dllimport )
#define EXPORT_API  extern "C" __declspec(dllimport )
#endif
#else
#define EXPORT_CLASS
#define EXPORT_API  extern "C" __attribute__((visibility("default")))
#define EXPORT_CLASS_API __attribute__((visibility("default")))
#endif

namespace facethink
{
    class EXPORT_CLASS RecFormulaRecognization{
    public:
        /**
         * @brief SDK初始化函数，必须先于其他SDK函数之前调用
         * @param [in] encoder_model_path encoder模型文件路径
         * @param [in] decoder_model_path decoder模型文件路径
         * @param [in] config_path SDK对应的ini配置文件路径，详见config.ini
         * @param [in] word_dict_path word_dict文件路径
         * @remarks 初始化构造函数需要读取模型等文件
        */
        EXPORT_CLASS_API static RecFormulaRecognization* create(const std::string& encoder_model_path, const std::string& decoder_model_path,
                                                                const std::string& config_path, const std::string& word_dict_path);

        /**
         * @brief 公式识别接口
         * @param [in] imgs 待识别的图片，只允许RGB和BGR格式，通过参数is_rgb_format指定
         * @param [out] formulas 识别出的公式
         * @param [out] confidences 识别结果的置信度
         * @param [in] is_rgb_format 识别出的公式是否为RGB格式
         * @return
         * @retval 0 成功
         * @retval -1 图片为空
        */
        EXPORT_CLASS_API virtual int detect(const std::vector<cv::Mat>& imgs, std::vector<std::string>& formulas, std::vector<float>& confidences, bool is_rgb_format = false) = 0;

        /**
         * @brief 析构函数
        */
        EXPORT_CLASS_API virtual ~RecFormulaRecognization(void);

    protected:
        EXPORT_CLASS_API explicit RecFormulaRecognization(void);
        RecFormulaRecognization(const RecFormulaRecognization&) = delete;
        RecFormulaRecognization& operator=(const RecFormulaRecognization&) = delete;
    };
}

#endif // __FACETHINK_API_REG_FORMULA_RECOGNIZATION_HPP__