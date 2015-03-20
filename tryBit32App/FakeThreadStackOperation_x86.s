
section .data
    top db 0x12,0x34,0x56,0x78,
        dq 0x2121212121212121
        dq 0x1111111111111111
        dq 0x2222222222222222
        dq 0x3333333333333333
    stack        db "this is the stack for try something, ok"
        db "this is the stack for try something, ok"
        db "this is the stack for try something, ok"
        db "this is the stack for try something, ok"
        db "this is the stack for try something, ok"
        db "this is the stack for try something, ok"
        db "this is the stack for try something, ok"
        db "this is the stack for try something, ok"
        db "this is the stack for try something, ok"

section .text

global FakeThread_GetRSP

global FakeThread_StartWithRsp
global FakeThread_YieldWithMainRsp
global FakeThread_ResumeWithThreadRsp
global FakeThread_GetItemPtr

; ------
global _FakeThread_GetRSP

global _FakeThread_StartWithRsp
global _FakeThread_YieldWithMainRsp
global _FakeThread_ResumeWithThreadRsp
global _FakeThread_GetItemPtr

_FakeThread_GetRSP:
FakeThread_GetRSP:
    mov eax, esp
    ret

; FakeThreadItem * FakeThread_GetItemPtr(long long llMainRsp);

_FakeThread_GetItemPtr:
FakeThread_GetItemPtr:
    push edx
    mov edx, esp
    mov esp, [edx + 8] ; llMainRsp 为目标栈
    sub esp, 4
    pop eax
    mov esp, edx
    pop edx
    ret

; FakeThreadItem * FakeThread_StartWithRsp(long long llNewRsp, void (*pfunc) (), FakeThreadItem *pItem, long long *pSaveMainRsp )

_FakeThread_StartWithRsp:
FakeThread_StartWithRsp:
    mov eax, [esp + 16]
    mov [eax], esp ; 第四个参数 保存main esp
    push dword [esp + 12]     ; 第三个参数 保存pItem
    push ebp

    mov eax, esp
    mov esp, [eax + 12] ; 第一个参数llNewRsp, 因为上面有两个push
    push eax ; fix align
    push eax ; fix align
    push eax
    push ebp

    call [eax + 16] ; 第二个参数, 因为上面有两个push

    pop ebp
    pop eax
    mov esp, eax

    pop ebp
    pop eax
    pop eax ; fix align
    pop eax ; fix align
    ret

; FakeThreadResumeParam * FakeThread_YieldWithMainRsp(long long llMainRsp, long long *pThreadRsp);
_FakeThread_YieldWithMainRsp:
FakeThread_YieldWithMainRsp:
    mov eax, [esp + 8]
    mov [eax], esp ; 第二个参数中保存当前栈位置
    push ebp

    mov esp, [esp + 8] ; 第一个参数是新栈, 注：上面有个push
    sub esp, 8
    pop ebp
    pop eax
    ret

; resume 函数
; void FakeThread_ResumeWithThreadRsp(long long llThreadRsp, long long *pSaveMainRsp, FakeThreadItem *pItem, FakeThreadResumeParam *pResumeParam)
_FakeThread_ResumeWithThreadRsp:
FakeThread_ResumeWithThreadRsp:
    mov eax, esp ; 这里保存下原先的栈位置，以便方问参数
    mov [eax + 8], esp ; 第二个参数用于保存当前栈
    push dword [eax + 12] ; 第三个参数: 新的伪线程对象
    push ebp

    mov esp, [eax + 4] ; 第一个参数是新栈
    sub esp, 4
    pop ebp
    mov eax, [eax + 16] ; 第四个参数是要返回的值
    ret
