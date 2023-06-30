
调用方式：
sh performance_run_gpu.sh  TEST_BATCH  TEST_ITER RESULT_PATH  TEST_LIST

TEST_BATCH  测试的最大batch
TEST_ITER   测试TEST_LIST 的轮数
RESULT_PATH 测试结果存储文件
TEST_LIST   测试图片LIST



调用实例：
sh performance_run_gpu.sh  1 2 result.txt ./data/img_100.list
