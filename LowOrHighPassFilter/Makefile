NAME := a.out

SRCS_DIR := srcs
OBJS_DIR := objs
HDRS_DIR := hdrs

CC       := g++
FLAGS    := -Wall -Wextra -O2 `pkg-config --cflags opencv4`
INCLUDES := -I./$(HDRS_DIR)
RM       := rm -f

LIBS := `pkg-config --libs opencv4`

CPPS := main.cpp BuildFrequencyMask.cpp ShiftDFT.cpp
SRCS := $(addprefix $(SRCS_DIR)/, $(CPPS))
OBJS := $(SRCS:$(SRCS_DIR)/%.cpp=$(OBJS_DIR)/%.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp
	@ mkdir -p $(OBJS_DIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(RM) -r $(OBJS_DIR)
	$(RM) *.png

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: clean re all fclean
