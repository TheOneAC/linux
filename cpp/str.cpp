/* character operation
 */

// memmove buffer for transfer to avoid src and dest overlap
void *memmove(void* dest, const void *src, size_t n){
	assert((src != nullptr) && (dest != nullptr));
	char* buffer = (char*)malloc(sizeof(char)*n);
	char* d = (char*)dest;
	const char* s = (const char*)src;
	size_t i;
	for(i = 0; i < n; i++)buffer[i] = s[i];
	for(i = 0; i < n; i++)d[i] = buffer[i];
	free(buffer);
	return dest;
}
//memmove in place
void *memmove(void* dest, const void *src, size_t n){
	const char* s = (const char*)src;
	char* d = (char*)dest;
	if(src < dest && src + n > dest){
		d += n-1;
		s += n-1;
		while(n-- > 0)*d-- = *s--;
	}else {
		while(n-- > 0)*d++ = *s++;
	}
	return dest;
}
// strcpy
char* strcpy(char* dest, const char* src){
	assert((src != nullptr) && (dest != nullptr));
	size_t i;
	for(i = 0;src[i] != '\0';i++)
		dest[i] = src[i];
	dest[i] = '\0';
	return dest;
}
// strcpy
char* strncpy(char* dest, const char* src,size_t n){
	assert((src != nullptr) && (dest != nullptr));
	size_t i;
	for(i = 0;i < n && src[i] != '\0';i++)
		dest[i] = src[i];
	while(i < n) dest[i++] = '\0';
	return dest;
}

//strlen
size_t strlen(const char* p){
	assert(p != nullptr);
	size_t size = 0;
	while(*p ++ != '\0')++size;
	return size;
}
// memset
void memset(void* dest, int c,size_t n){
	char* d = (char*)dest;
	assert(d != nullptr);
	while(n-- > 0)*d++ = (char)c;
	return dest;
}
// strcmp
int strcmp(const char* str1, const char* str2){
	while(*str1 != '\0' && *str2 != '\0' && *str1++ == *str2++);
	if(*str1 == '\0' && *str2 == '\0')return 0;
	else if(*str1 == '\0')return -1;
	else return 1;
}
