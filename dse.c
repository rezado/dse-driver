#include <stdint.h>
#include <stdio.h>
#include "dse.h"


static const uint64_t robsize_array[] = {256, 128, 64, 32, 16, 8, 4, 2};
// static const uint64_t robsize_array[] = {64};
// static const uint64_t lqsize_array[] = {256, 128, 64, 32, 16, 12, 8, 4, 2};
static const uint64_t lqsize_array[] = {32};
// static const uint64_t sqsize_array[] = {256, 128, 64, 32, 16, 12, 8, 4, 2};
static const uint64_t sqsize_array[] = {24};
// static const uint64_t ftqsize_array[] = {128, 64, 32, 16, 12, 8, 4, 2};
static const uint64_t ftqsize_array[] = {16};
// static const uint64_t ibsize_array[] = {256, 128, 64, 32, 16, 12, 8, 4, 2};
static const uint64_t ibsize_array[] = {16};
static const uint64_t intdqsize_array[] = {12, 8, 4, 2};
static const uint64_t fpdqsize_array[] = {12, 8, 4, 2};
static const uint64_t lsdqsize_array[] = {12, 8, 4, 2};


void main() {

    // 写入 MAX_INSTR_REG
    *(volatile uint64_t *)MAX_INSTR_REG = MAX_INSTR_CNT;

    // 写入 MAX_EPOCH_REG
    *(volatile uint64_t *)MAX_EPOCH_REG = sizeof(intdqsize_array) / sizeof(intdqsize_array[0]);

    // 读取 ping-pong 寄存器并反转
    *(volatile uint8_t *)PINGPONG_REG ^= 1;

    // 读取 EPOCH_REG 寄存器
    uint64_t epoch = *(volatile uint64_t *)EPOCH_REG;

    // 根据 ctrlsel 写入 robsize 寄存器
    // if (*(volatile uint8_t *)PINGPONG_REG == 0) {
    //     *(volatile uint64_t *)ROBSIZE0_REG = robsize_array[epoch % (sizeof(robsize_array) / sizeof(robsize_array[0]))];
    // } else {
    //     *(volatile uint64_t *)ROBSIZE1_REG = robsize_array[epoch % (sizeof(robsize_array) / sizeof(robsize_array[0]))];
    // }

    // 根据 ctrlsel 写入参数寄存器
    if (*(volatile uint8_t *)PINGPONG_REG == 0) {
        *(volatile uint64_t *)ROBSIZE0_REG = robsize_array[epoch % (sizeof(robsize_array) / sizeof(robsize_array[0]))];
        *(volatile uint64_t *)LQSIZE0_REG = lqsize_array[epoch % (sizeof(lqsize_array) / sizeof(lqsize_array[0]))];
        *(volatile uint64_t *)SQSIZE0_REG = sqsize_array[epoch % (sizeof(sqsize_array) / sizeof(sqsize_array[0]))];
        *(volatile uint64_t *)FTQ0_REG = ftqsize_array[epoch % (sizeof(ftqsize_array) / sizeof(ftqsize_array[0]))];
        *(volatile uint64_t *)IBUFSIZE0_REG = ibsize_array[epoch % (sizeof(ibsize_array) / sizeof(ibsize_array[0]))];
        *(volatile uint64_t *)INTDQSIZE0_REG = intdqsize_array[epoch % (sizeof(intdqsize_array) / sizeof(intdqsize_array[0]))];
        *(volatile uint64_t *)FPDQSIZE0_REG = fpdqsize_array[epoch % (sizeof(fpdqsize_array) / sizeof(fpdqsize_array[0]))];
        *(volatile uint64_t *)LSDQSIZE0_REG = lsdqsize_array[epoch % (sizeof(lsdqsize_array) / sizeof(lsdqsize_array[0]))];
    } else {
        *(volatile uint64_t *)ROBSIZE1_REG = robsize_array[epoch % (sizeof(robsize_array) / sizeof(robsize_array[0]))];
        *(volatile uint64_t *)LQSIZE1_REG = lqsize_array[epoch % (sizeof(lqsize_array) / sizeof(lqsize_array[0]))];
        *(volatile uint64_t *)SQSIZE1_REG = sqsize_array[epoch % (sizeof(sqsize_array) / sizeof(sqsize_array[0]))];
        *(volatile uint64_t *)FTQ1_REG = ftqsize_array[epoch % (sizeof(ftqsize_array) / sizeof(ftqsize_array[0]))];
        *(volatile uint64_t *)IBUFSIZE1_REG = ibsize_array[epoch % (sizeof(ibsize_array) / sizeof(ibsize_array[0]))];
        *(volatile uint64_t *)INTDQSIZE1_REG = intdqsize_array[epoch % (sizeof(intdqsize_array) / sizeof(intdqsize_array[0]))];
        *(volatile uint64_t *)FPDQSIZE1_REG = fpdqsize_array[epoch % (sizeof(fpdqsize_array) / sizeof(fpdqsize_array[0]))];
        *(volatile uint64_t *)LSDQSIZE1_REG = lsdqsize_array[epoch % (sizeof(lsdqsize_array) / sizeof(lsdqsize_array[0]))];
    }

    // 打印信息
    // if (*(volatile uint8_t *)PINGPONG_REG == 0) {
    //     printf("epoch %ld: robsize0 %ld, lqsize0 %ld, sqsize0 %ld, ftqsize0 %ld, ibufsize0 %ld\n", epoch,
    //         *(volatile uint64_t *)ROBSIZE0_REG, *(volatile uint64_t *)LQSIZE0_REG, *(volatile uint64_t *)SQSIZE0_REG,
    //         *(volatile uint64_t *)FTQ0_REG, *(volatile uint64_t *)IBUFSIZE0_REG);
    // } else {
    //     printf("epoch %ld: robsize1 %ld, lqsize1 %ld, sqsize1 %ld, ftqsize1 %ld, ibufsize1 %ld\n", epoch,
    //         *(volatile uint64_t *)ROBSIZE1_REG, *(volatile uint64_t *)LQSIZE1_REG, *(volatile uint64_t *)SQSIZE1_REG,
    //         *(volatile uint64_t *)FTQ1_REG, *(volatile uint64_t *)IBUFSIZE1_REG);
    // }

    // 增加 epoch
    *(volatile uint64_t *)EPOCH_REG = epoch + 1;

    // 写入 ctrlsel 寄存器
    *(volatile uint8_t *)CTRLSEL_REG = *(volatile uint8_t *)PINGPONG_REG;
}