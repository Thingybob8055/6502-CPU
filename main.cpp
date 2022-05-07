#include <iostream>
#include <sstream>

#include "bus.h"
#include "6502cpu.h"

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine/olcPixelGameEngine.h"

//BORROWED FROM OLCNES
class Demo_6502 : public olc::PixelGameEngine
{
public:
	Demo_6502() { sAppName = "6502 Demonstration"; }

	bus nes;
	std::map<uint16_t, std::string> mapAsm;

	std::string hex(uint32_t n, uint8_t d)
	{
		std::string s(d, '0');
		for (int i = d - 1; i >= 0; i--, n >>= 4)
			s[i] = "0123456789ABCDEF"[n & 0xF];
		return s;
	};

	void DrawRam(int x, int y, uint16_t nAddr, int nRows, int nColumns)
	{
		int nRamX = x, nRamY = y;
		for (int row = 0; row < nRows; row++)
		{
			std::string sOffset = "$" + hex(nAddr, 4) + ":";
			for (int col = 0; col < nColumns; col++)
			{
				sOffset += " " + hex(nes.bus_read(nAddr), 2);
				nAddr += 1;
			}
			DrawString(nRamX, nRamY, sOffset);
			nRamY += 10;
		}
	}

	void DrawCpu(int x, int y)
	{
		std::string status = "STATUS: ";
		DrawString(x , y , "STATUS:", olc::WHITE);
		DrawString(x  + 64, y, "N", nes.nes_cpu.status & cpu::Negative ? olc::GREEN : olc::RED);
		DrawString(x  + 80, y , "V", nes.nes_cpu.status & cpu::Overflow ? olc::GREEN : olc::RED);
		DrawString(x  + 96, y , "-", nes.nes_cpu.status & cpu::Unused ? olc::GREEN : olc::RED);
		DrawString(x  + 112, y , "B", nes.nes_cpu.status & cpu::Break ? olc::GREEN : olc::RED);
		DrawString(x  + 128, y , "D", nes.nes_cpu.status & cpu::Decimal ? olc::GREEN : olc::RED);
		DrawString(x  + 144, y , "I", nes.nes_cpu.status & cpu::Disable_Interrupts ? olc::GREEN : olc::RED);
		DrawString(x  + 160, y , "Z", nes.nes_cpu.status & cpu::Zero ? olc::GREEN : olc::RED);
		DrawString(x  + 178, y , "C", nes.nes_cpu.status & cpu::Carry ? olc::GREEN : olc::RED);
		DrawString(x , y + 10, "PC: $" + hex(nes.nes_cpu.pc, 4));
		DrawString(x , y + 20, "A: $" +  hex(nes.nes_cpu.accu, 2) + "  [" + std::to_string(nes.nes_cpu.accu) + "]");
		DrawString(x , y + 30, "X: $" +  hex(nes.nes_cpu.x_reg, 2) + "  [" + std::to_string(nes.nes_cpu.x_reg) + "]");
		DrawString(x , y + 40, "Y: $" +  hex(nes.nes_cpu.y_reg, 2) + "  [" + std::to_string(nes.nes_cpu.y_reg) + "]");
		DrawString(x , y + 50, "SP: $" + hex(nes.nes_cpu.sp, 4));
	}

	bool OnUserCreate()
	{
		// Load Program (assembled at https://www.masswerk.at/6502/assembler.html)
		/*
			*=$8000
			LDX #10
			STX $0000
			LDX #3
			STX $0001
			LDY $0000
			LDA #0
			CLC
			loop
			ADC $0001
			DEY
			BNE loop
			STA $0002
			NOP
			NOP
			NOP
		*/
		
		// Convert hex string into bytes for RAM
		std::stringstream ss;
		ss << "A2 0A 8E 00 00 A2 03 8E 01 00 AC 00 00 A9 00 18 6D 01 00 88 D0 FA 8D 02 00 EA EA EA";
		uint16_t nOffset = 0x8000;
		while (!ss.eof())
		{
			std::string b;
			ss >> b;
			nes.memory[nOffset++] = (uint8_t)std::stoul(b, nullptr, 16);
		}

		// Set Reset Vector
		nes.memory[0xFFFC] = 0x00;
		nes.memory[0xFFFD] = 0x80;

		// Dont forget to set IRQ and NMI vectors if you want to play with those
				
		// Reset
		nes.nes_cpu.reset();
		return true;
	}

	bool OnUserUpdate(float fElapsedTime)
	{
		Clear(olc::DARK_BLUE);


		if (GetKey(olc::Key::SPACE).bPressed)
		{
			do
			{
				nes.nes_cpu.cpu_clock();
			} 
			while (!nes.nes_cpu.complete());
		}

		if (GetKey(olc::Key::R).bPressed)
			nes.nes_cpu.reset();

		if (GetKey(olc::Key::I).bPressed)
			nes.nes_cpu.interrupt_request();

		if (GetKey(olc::Key::N).bPressed)
			nes.nes_cpu.non_mask_interrupt();

		// Draw Ram Page 0x00		
		DrawRam(2, 2, 0x0000, 16, 16);
		DrawRam(2, 182, 0x8000, 16, 16);
		DrawCpu(462, 142);
		
		DrawString(10, 430, "SPACE = Step Instruction    R = RESET    I = IRQ    N = NMI");

		return true;
	}
};


int main() {
    Demo_6502 demo;
	demo.Construct(680, 480, 2, 2);
	demo.Start();
	return 0;
}