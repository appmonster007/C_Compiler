YFLAGS		= -d -v
GF			= grammarfile
LF			= lexfile
OBJS		= $(GF).tab.o lex.yy.o symbolTable.o
SRCS		= $(GF).tab.c lex.yy.c symbolTable.c
CC			= gcc 
PROGRAM		= parser lexer code


all:		$(PROGRAM)  


parser:		$(GF).y
		bison $(YFLAGS) $(GF).y

lexer:		$(LF).l 
		flex $(LF).l

.c.o:		$(SRCS)
		$(CC) -c $*.c -o $@ -O

code:		$(OBJS)
		$(CC) $(OBJS) -o $@ -lfl -lm

clean:;	rm ‑f $(OBJS) *.o $(PROGRAM) y.* y.tab.* *.output
