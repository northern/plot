
PROG_NAME = plot
CC        = gcc
LD        = gcc
CFLAG     = -Wall -Wno-deprecated-declarations

SRC_DIR   = ./src
BLD_DIR   = ./build
BIN_DIR   = ./bin
RES_DIR   = $(SRC_DIR)/resource
AST_DIR   = ./assets

SRC = \
	main.c \
	appwindow.c \

OBJ = $(SRC:.c=.o)

$(PROG_NAME): resources $(OBJ)
	$(LD) $(subst $(space),$(comma),$(addprefix $(BLD_DIR)/,$(OBJ))) `pkg-config --libs gtk+-2.0` -o $(BIN_DIR)/$@

%.o:
	$(CC) $(CFLAG) `pkg-config --cflags gtk+-2.0` -o $(BLD_DIR)/$@ -c $(SRC_DIR)/$*.c

resources:
	gdk-pixbuf-csource --raw --name=image_icon $(AST_DIR)/icon.png > $(RES_DIR)/icon.h

up:
	cd $(BIN_DIR) && ./$(PROG_NAME)

clean:
	rm -f $(BIN_DIR)/$(PROG_NAME) $(BLD_DIR)/*.o
