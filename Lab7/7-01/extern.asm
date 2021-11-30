.data
extern CreateThread: proc

mutex dw 0								; ������ ���������� DWORD

.code
ExecuteWork proc
	mov rax, 1000000					; ���������� �������� � ������� rax

SpinLoop:								; ����� ������������� ��������� ������ 
	lock bts mutex, 0					; ��������� ���������� � ���� ������ ������������� mutex = 1 � ���� fc = 0
	jc SpinLoop							; ��������� ����� ������������� ������ ����� �����, ���� �� ��������� ������


										; critical section
	mov rdx, 1000
InnerLoop:								; 1000 �������� ������ �������
	inc dword ptr [rcx]

	dec rdx
	jnz InnerLoop

										; ����������� �����, ������� ���������� � SpinLoop
	mov mutex, 0
										; end  critical section
	sub rax, 1000						; �������� � �������� 1000
	jnz SpinLoop						; ��������� � ������� ����� ���� �� ���������� ��� ��������

	ret
ExecuteWork endp

CreateThreadInAsm proc
	push rbp							; Save the caller's RBP
	mov rbp, rsp						; Save rsp of stack frame

	push 0								; Thread id
	push 0								; Creation flags, start immediately

	sub rsp, 20h						; Reserve 4 quads of shadow space

	mov r9, rcx							; Move *i to r9
	mov rcx, 0							; Security attrs
	mov rdx, 0							; Use the same stack size as calling thread
	mov r8, ExecuteWork

	call CreateThread

	mov rsp, rbp
	pop rbp								;Restore the callres RBP

	ret 
CreateThreadInAsm endp

end


	