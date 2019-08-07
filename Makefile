NAME = lem-in

CC = gcc
FLAGS = -g

SRCDIR = srcs/
OBJDIR = obj/

FILES = algorithm	algorithm2	algorithm3	algorithm4\
block	block2	check	free	handle_errors	lem-in\
print	print2	reading_data1	reading_data2	reading_data3
SRC = $(addprefix $(SRCDIR), $(addsuffix .c,$(FILES)))
OBJ = $(addprefix $(OBJDIR),$(addsuffix .o,$(FILES)))

LIBFT = ./ft_printf/libftprintf.a
INCDIR = -I ./includes
LIBLINK = -L ./ft_printf -lftprintf
LIBINC = -I ./ft_printf/includes

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C ./ft_printf

$(OBJDIR):
	@echo "Creating Lem-in object files directory..."
	@mkdir $(OBJDIR)
	@echo "Directory created!"

$(OBJDIR)%.o: $(SRCDIR)%.c | $(OBJDIR)
	@$(CC) $(FLAGS) $(INCDIR) $(LIBINC) -c $< -o $@

$(NAME): $(OBJ)
	@echo "Compiling Lem-in..."
	@$(CC) $(LIBLINK) -o $(NAME) $(OBJ)
	@echo "Lem-in is compiled!"

libclean:
	@make clean -C ./ft_printf

clean: libclean
	@echo "Deleting Lem-in object files..."
	@rm -rf $(OBJDIR)
	@echo "Lem-in object files are deleted!"

fclean: clean
	@echo "Deleting lem-in executable..."
	@rm -rf $(NAME)
	@echo "Executable is deleted!"
	@make fclean -C ./ft_printf
	@echo "Everything is cleaned!"

re: fclean
	@$(MAKE) all