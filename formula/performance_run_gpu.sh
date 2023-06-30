
export LD_LIBRARY_PATH=./lib/:$LD_LIBRARY_PATH

# Set encoder model path
ENCODER_MODEL_PATH_1=./model/rec_formula_recognization_encoder_v1.0.1.pt
ENCODER_MODEL_PATH_2=./model/rec_formula_recognization_encoder_v1.0.2.pt
ENCODER_MODEL_PATH_3=./model/rec_formula_recognization_encoder_v1.0.0.pt

# Set decoder model path
DECODER_MODEL_PATH_1=./model/rec_formula_recognization_decoder_v1.0.1.pt
DECODER_MODEL_PATH_2=./model/rec_formula_recognization_decoder_v1.0.2.pt
DECODER_MODEL_PATH_3=./model/rec_formula_recognization_decoder_v1.0.0.pt

# Set word dict path
WORD_DICT_PATH=./model/rec_formula_recognization_words_v1.0.0.txt

#Set the config path
CONFIG_PATH_1=./model/config_1.ini
CONFIG_PATH_2=./model/config_2.ini
CONFIG_PATH_3=./model/config_0.ini

# Set test data
#IMAGES_PATH=./data/img_100.list
IMAGES_PATH=./data/merge_4000.list
#IMAGES_PATH=./data/test_case.list
#IMAGES_PATH=./data/mul_1000.list

# set batch_test
BATCH_TEST=$1

./test_det $ENCODER_MODEL_PATH_1  $ENCODER_MODEL_PATH_2  $ENCODER_MODEL_PATH_3  $DECODER_MODEL_PATH_1  $DECODER_MODEL_PATH_2 $DECODER_MODEL_PATH_3 	$CONFIG_PATH_1 $CONFIG_PATH_2  $CONFIG_PATH_3 $WORD_DICT_PATH $IMAGES_PATH $BATCH_TEST
