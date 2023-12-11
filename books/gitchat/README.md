# RUN ENVIRONMENT: 32B System
gcc test.c -fno-stack-protector

# Supplement
64B System compile 32B program 
gcc test.c -m32 -fno-stack-protector (64B)
