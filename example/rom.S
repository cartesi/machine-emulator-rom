// Copyright Cartesi and individual authors (see AUTHORS)
// SPDX-License-Identifier: Apache-2.0
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

.section .tohost
.align 3;
.global tohost; tohost: .quad 0;
.global fromhost; fromhost: .quad 0;

// Uses HTIF to exit the emulator with exit code in an immediate
#define exit_imm(imm) \
	li gp, imm; \
        j exit;

// Uses HTIF to exit the emulator with exit code in an immediate
#define exit_reg(reg) \
	mv gp, reg; \
        j exit;

// Section with code
.section .text.init
.align 2;
    // Set the exception handler to trap
    // This is just in case an exception happens
	la t0, trap;
	csrw mtvec, t0;

    // Your code goes here
    // In the example, we are simply adding two immediates
//    li a0, 1;
 //   addi a0, a0, 1;
	li a0, 0x808;
	ld a1, 0(a0);
	exit_reg(a1);

    // Exits with exit code 0
    exit_imm(0);

// The exception handler simply copies the cause to register
// gp and falls through to exit
trap:
	csrr gp, mcause;

// Exits via HTIF using gp contains the exit code
exit:
	// HTIF exits with dev = cmd = 0 and a payload with lsb set.
    // the exit code is taken from payload >> 2
	slli gp, gp, 16;
	srli gp, gp, 15;
	ori gp, gp, 1;
1:
    sd gp, tohost, t5;
    j 1b; // Should not be necessary
