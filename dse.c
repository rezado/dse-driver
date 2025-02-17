#include <stdint.h>
#include "dse.h"


// // static const uint64_t robsize_array[] = {256, 128, 64, 32, 16, 8, 4, 2};
// static const uint64_t robsize_array[] = {64};
// // static const uint64_t lqsize_array[] = {256, 128, 64, 32, 16, 12, 8, 4, 2};
// static const uint64_t lqsize_array[] = {32};
// // static const uint64_t sqsize_array[] = {256, 128, 64, 32, 16, 12, 8, 4, 2};
// static const uint64_t sqsize_array[] = {24};
// // static const uint64_t ftqsize_array[] = {128, 64, 32, 16, 12, 8, 4, 2};
// static const uint64_t ftqsize_array[] = {16};
// // static const uint64_t ibsize_array[] = {256, 128, 64, 32, 16, 12, 8, 4, 2};
// static const uint64_t ibsize_array[] = {16};
// // static const uint64_t intdqsize_array[] = {12, 8, 4, 2};
// static const uint64_t intdqsize_array[] = {12};
// // static const uint64_t fpdqsize_array[] = {12, 8, 4, 2};
// static const uint64_t fpdqsize_array[] = {12};
// // static const uint64_t lsdqsize_array[] = {12, 8, 4, 2};
// static const uint64_t lsdqsize_array[] = {12};
// // static const uint64_t l2mshrs_array[] = {14, 6, 1};
// static const uint64_t l2mshrs_array[] = {14};
// // static const uint64_t l3mshrs_array[] = {14, 6, 1};
// static const uint64_t l3mshrs_array[] = {14};
// // static const uint64_t l2sets_array[] = {128, 64};
// static const uint64_t l2sets_array[] = {128};
// static const uint64_t l3sets_array[] = {1024, 512};
// // static const uint64_t l3sets_array[] = {1024};

__attribute__((aligned(4)))
void main() {
    // 写入 MAX_INSTR_REG
    *(volatile uint64_t *)MAX_INSTR_REG = MAX_INSTR_CNT;

    // 写入 MAX_EPOCH_REG
    *(volatile uint64_t *)MAX_EPOCH_REG = 2;

    // 读取 ping-pong 寄存器并反转
    *(volatile uint8_t *)PINGPONG_REG ^= 1;

    // 读取 EPOCH_REG 寄存器
    uint64_t epoch = *(volatile uint64_t *)EPOCH_REG;


    // 根据 ctrlsel 写入参数寄存器
    if (*(volatile uint8_t *)PINGPONG_REG == 0) {
        *(volatile uint64_t *)ROBSIZE0_REG = *(volatile uint64_t *)ROBSIZE_ADDR;
        *(volatile uint64_t *)LQSIZE0_REG = *(volatile uint64_t *)LQSIZE_ADDR;
        *(volatile uint64_t *)SQSIZE0_REG = *(volatile uint64_t *)SQSIZE_ADDR;
        *(volatile uint64_t *)FTQ0_REG = *(volatile uint64_t *)FTQSIZE_ADDR;
        *(volatile uint64_t *)IBUFSIZE0_REG = *(volatile uint64_t *)IBUFSIZE_ADDR;
        *(volatile uint64_t *)INTDQSIZE0_REG = *(volatile uint64_t *)INTDQSIZE_ADDR;
        *(volatile uint64_t *)FPDQSIZE0_REG = *(volatile uint64_t *)FPDQSIZE_ADDR;
        *(volatile uint64_t *)LSDQSIZE0_REG = *(volatile uint64_t *)LSDQSIZE_ADDR;
        *(volatile uint64_t *)L2MSHRS0_REG = *(volatile uint64_t *)L2MSHRS_ADDR;
        *(volatile uint64_t *)L3MSHRS0_REG = *(volatile uint64_t *)L3MSHRS_ADDR;
        *(volatile uint64_t *)L2SETS0_REG = *(volatile uint64_t *)L2SETS_ADDR;
        *(volatile uint64_t *)L3SETS0_REG = *(volatile uint64_t *)L3SETS_ADDR;
    } else {
        *(volatile uint64_t *)ROBSIZE1_REG = *(volatile uint64_t *)ROBSIZE_ADDR;
        *(volatile uint64_t *)LQSIZE1_REG = *(volatile uint64_t *)LQSIZE_ADDR;
        *(volatile uint64_t *)SQSIZE1_REG = *(volatile uint64_t *)SQSIZE_ADDR;
        *(volatile uint64_t *)FTQ1_REG = *(volatile uint64_t *)FTQSIZE_ADDR;
        *(volatile uint64_t *)IBUFSIZE1_REG = *(volatile uint64_t *)IBUFSIZE_ADDR;
        *(volatile uint64_t *)INTDQSIZE1_REG = *(volatile uint64_t *)INTDQSIZE_ADDR;
        *(volatile uint64_t *)FPDQSIZE1_REG = *(volatile uint64_t *)FPDQSIZE_ADDR;
        *(volatile uint64_t *)LSDQSIZE1_REG = *(volatile uint64_t *)LSDQSIZE_ADDR;
        *(volatile uint64_t *)L2MSHRS1_REG = *(volatile uint64_t *)L2MSHRS_ADDR;
        *(volatile uint64_t *)L3MSHRS1_REG = *(volatile uint64_t *)L3MSHRS_ADDR;
        *(volatile uint64_t *)L2SETS1_REG = *(volatile uint64_t *)L2SETS_ADDR;
        *(volatile uint64_t *)L3SETS1_REG = *(volatile uint64_t *)L3SETS_ADDR;
    }


    // 增加 epoch
    *(volatile uint64_t *)EPOCH_REG = epoch + 1;

    // 写入 ctrlsel 寄存器
    *(volatile uint8_t *)CTRLSEL_REG = *(volatile uint8_t *)PINGPONG_REG;
}
