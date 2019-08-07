NAME := libftprintf.a

PFDIR := printf/
PF :=   flag_specifier flag_specifier2	ft_printf precise_specifier	\
		precise_specifier2 process_specifier process_specifier2 process_specifier3 \
		type_specifier	type_specifier2	width_specifier check_smth \

LIBDIR := libft/
LIB :=	ft_atoi ft_bzero ft_isalnum ft_isalpha ft_isascii \
    ft_isdigit ft_isprint ft_memccpy ft_memchr ft_memcmp \
    ft_memcpy ft_memmove ft_memset ft_putchar ft_putstr \
    ft_strcat ft_strchr ft_strcmp ft_strcpy ft_strdup \
    ft_strlcat ft_strlen ft_strncat ft_strncmp ft_strncpy \
    ft_strnstr ft_strrchr ft_strstr ft_tolower ft_toupper \
    ft_memalloc ft_memdel ft_memdel ft_strdel ft_strclr \
    ft_striter ft_striteri ft_strmap ft_strmapi ft_strequ \
    ft_strnequ ft_strsub ft_strjoin ft_strtrim ft_strsplit \
    ft_itoa ft_putendl ft_putnbr ft_putchar_fd ft_putstr_fd \
    ft_putendl_fd ft_putnbr_fd ft_strnew \
	ft_lstnew ft_lstdelone ft_lstdel ft_lstadd ft_lstiter \
    ft_itoa_base ft_fitoa ft_uitoa \
	get_next_line ft_uniswap ft_arrset ft_arrcpy

COMPILE := gcc -Wall -Wextra -Werror -g
OBJDIR := obj/
SRCDIR := srcs/
INCDIR := includes/

FILES := $(addprefix $(PFDIR),$(PF))
FILES += $(addprefix $(LIBDIR),$(LIB))

SRC := $(addprefix $(SRCDIR),$(addsuffix .c,$(FILES)))
OBJ := $(addprefix $(OBJDIR),$(addsuffix .o,$(FILES)))

all: $(NAME)

$(OBJDIR):
	@echo "Creating object files directories..."
	@mkdir $(OBJDIR)
	@mkdir $(OBJDIR)$(PFDIR)
	@mkdir $(OBJDIR)$(LIBDIR)
	@echo "OK!"

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	@$(COMPILE) -I $(INCDIR) -c $< -o $@

$(NAME): $(OBJ)
	@echo "Compiling library..."
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "OK!"

clean:
	@echo "Deleting object files..."
	@rm -rf $(OBJDIR)
	@rm -f $(OBJMKDIR)
	@echo "OK!"

fclean: clean
	@echo "Deleting library binary..." 
	@rm -f $(NAME)
	@echo "OK!"

re: fclean
	@$(MAKE) all

test: all
	@echo "Compiling test..."
	@$(COMPILE) -w -I$(INCDIR) -L. -lftprintf main.c -o test
	@echo "OK!"