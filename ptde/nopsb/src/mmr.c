
 byte asm_sz(void *asm1) {
WORD w1 = 0xc390; byte x=0;
for (byte i = 0; i < 30; i++)
if (memcmp(asm1+i,&w1,2) == 0) 
{x = i;break;} 
return x;
 }

byte usz(void *src, byte sz)
{
if (sz == 0) sz = asm_sz(src);
//if (sz == 'b') sz = sizeof(src);
DEBUG_PRINT("size: %i\n", sz);
return sz;
}

void wp(void *dst, void *src, byte sz)
{
if (!dst) return;
sz = usz(src, sz);
if (sz == 0) return;

DWORD op1 = 0x40;
 VirtualProtect(dst, sz, op1, &op1);
memcpy(dst,src,sz);
 VirtualProtect(dst, sz, op1, &op1);
}

DWORD msz(void *hModule) 
{
PIMAGE_DOS_HEADER pImage_Dos_Header = (PIMAGE_DOS_HEADER)hModule;
PIMAGE_NT_HEADERS pImage_PE_Header = (PIMAGE_NT_HEADERS)( (long)hModule + pImage_Dos_Header->e_lfanew );
return pImage_PE_Header->OptionalHeader.SizeOfImage;
}

void *sigscan(void *sig, byte sz) 
{
sz = usz(sig, sz);
void *x=NULL;
if (sz == 0) return x;

void *hModule = GetModuleHandle(NULL);

DWORD msz1 = msz(hModule);

for (int i = 0; i < msz1-sz; i++) 
if (memcmp(hModule+i,sig,sz) == 0) 
 {x = hModule+i; DEBUG_PRINT("sigscan: x = %p i = %x \n",x, i); break;}

 return x;
}