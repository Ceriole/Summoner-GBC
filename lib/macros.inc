macro lb
	assert (\2) < 256
	assert (\3) < 256
	ld \1, (\2) << 8 | (\3)
endm