#include "lib.hpp"

/* Define hook StubCopyright. Trampoline indicates the original function should be kept. */
/* HOOK_DEFINE_REPLACE can be used if the original function does not need to be kept. */

void* new_local_3a48 = 0; //sp + #0x18
void* new_local_3248 = 0; //sp + #0x818
void* new_local_2a48 = 0; //sp,#0x1, LSL #12 + 0x18
void* new_local_2248 = 0; //sp,#0x1, LSL #12 + 0x818
void* new_local_1a48 = 0; //sp,#0x2, LSL #12 + 0x18
void* new_local_1248 = 0; //sp,#0x2, LSL #12 + 0x818
void* new_local_a48 = 0; //sp,#0x3, LSL #12 + 0x18

HOOK_DEFINE_TRAMPOLINE(textRender) {

	/* Define the callback for when the function is called. Don't forget to make it static and name it Callback. */
	static uint64_t Callback(void* x0, void* x1, const char* string, void* x3, void* x4, void* x5, void* x6, double d0, double d1, double d2, double d3, double d4) {
		static bool initialized = false;
		if (!initialized) {
			uint32_t buffer_character_size = 2048;
			new_local_3a48 = calloc(buffer_character_size, sizeof(int));
			new_local_3248 = calloc(buffer_character_size, sizeof(int));
			new_local_2a48 = calloc(buffer_character_size, sizeof(int));
			new_local_2248 = calloc(buffer_character_size, sizeof(int));
			new_local_1a48 = calloc(buffer_character_size, sizeof(int));
			new_local_1248 = calloc(buffer_character_size, sizeof(int));
			new_local_a48 = calloc(buffer_character_size, sizeof(int));
			initialized = true;
		}
		return Orig(x0, x1, string, x3, x4, x5, x6, d0, d1, d2, d3, d4);
	}

};

HOOK_DEFINE_INLINE(InlineHook0) {
	static void Callback(exl::hook::nx64::InlineCtx* ctx) {
		/*
		ctx -> X[1] = (uint64_t)new_local_3a48;
		ctx -> X[3] = (uint64_t)new_local_3248;
		ctx -> X[4] = (uint64_t)new_local_1a48;
		ctx -> X[7] = (uint64_t)new_local_2248;
		ctx -> X[19] = (uint64_t)new_local_2a48;
		ctx -> X[22] = (uint64_t)new_local_1248;
		ctx -> X[26] = (uint64_t)new_local_a48;
		*/
	}
};

HOOK_DEFINE_INLINE(InlineHook1) {
	static void Callback(exl::hook::nx64::InlineCtx* ctx) {
		/*
		ctx -> X[19] = (uint64_t)new_local_3a48;
		ctx -> X[20] = (uint64_t)new_local_3248;
		ctx -> X[24] = (uint64_t)new_local_1248;
		ctx -> X[25] = (uint64_t)new_local_1a48;
		ctx -> X[27] = (uint64_t)new_local_2248;
		ctx -> X[26] = (uint64_t)new_local_a48;
		*/
	}
};

HOOK_DEFINE_INLINE(InlineHook2) {
	static void Callback(exl::hook::nx64::InlineCtx* ctx) {
		/*
		ctx -> X[19] = (uint64_t)new_local_2248;
		ctx -> X[20] = (uint64_t)new_local_1a48;
		ctx -> X[24] = (uint64_t)new_local_1248;
		ctx -> X[25] = (uint64_t)new_local_1a48;
		ctx -> X[27] = (uint64_t)new_local_3a48;
		ctx -> X[28] = (uint64_t)new_local_3248;
		ctx -> X[26] = (uint64_t)new_local_a48;
		*/
	}
};

HOOK_DEFINE_INLINE(InlineHook3) {
	static void Callback(exl::hook::nx64::InlineCtx* ctx) {
		/*
		ctx -> X[1] = (uint64_t)new_local_3a48;
		ctx -> X[3] = (uint64_t)new_local_3248;
		ctx -> X[4] = (uint64_t)new_local_1a48;
		ctx -> X[7] = (uint64_t)new_local_2248;
		ctx -> X[22] = (uint64_t)new_local_1248;
		*/
	}
};

HOOK_DEFINE_INLINE(InlineHook4) {
	static void Callback(exl::hook::nx64::InlineCtx* ctx) {
		//ctx -> X[0] = (uint64_t)new_local_a48;
	}
};

HOOK_DEFINE_INLINE(InlineHook5) {
	static void Callback(exl::hook::nx64::InlineCtx* ctx) {
		//ctx -> X[19] = (uint64_t)new_local_2a48;
	}
};

extern "C" void exl_main(void* x0, void* x1) {
	/* Setup hooking enviroment. */
	exl::hook::Initialize();
	textRender::InstallAtOffset(0x4DF40);
	/* Alternative install funcs: */
	/* InstallAtPtr takes an absolute address as a uintptr_t. */
	/* InstallAtOffset takes an offset into the main module. */
	
	InlineHook0::InstallAtOffset(0x4E254); // Causes text rendering glitches
	/*
	InlineHook1::InstallAtOffset(0x4E570); // No problems (it may just not be used)
	InlineHook2::InstallAtOffset(0x4E654); // Causes text rendering glitches
	InlineHook3::InstallAtOffset(0x4E4D8); // No problems (it may just not be used)
	InlineHook4::InstallAtOffset(0x4E130); // No problems (it may just not be used) 
	InlineHook5::InstallAtOffset(0x4E500); // Causing infinite loop in pair with other hooks, alone it crashes game
	*/

	exl::patch::CodePatcher p(0x4DDFC);
	p.WriteInst(0xD366FE31);
	p.Seek(0x4DE90);
	p.WriteInst(0xD366FDCE);
}

extern "C" NORETURN void exl_exception_entry() {
	/* TODO: exception handling */
	EXL_ABORT(0x420);
}
