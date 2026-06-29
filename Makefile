# Makefile

# OS Detection
ifeq ($(OS),Windows_NT)
    RM = del /F /Q
    RMDIR = rmdir /S /Q
    MKDIR = mkdir
    EXE = .exe
    NULL = NUL
else
    RM = rm -f
    RMDIR = rm -rf
    MKDIR = mkdir -p
    EXE =
    NULL = /dev/null
endif

# Compiler
CXX       = g++
CXXFLAGS  = -std=c++17 -O3 -Wall -Wextra -Iinclude
LDFLAGS   =

TARGET    = heat_sim$(EXE)
SRCDIR    = src
OBJDIR    = obj
SRCS      = $(wildcard $(SRCDIR)/*.cpp)
OBJS      = $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SRCS))

# ============================================================
# Target
# ============================================================
all: $(TARGET)

# Lien
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	-@$(MKDIR) $(OBJDIR) 2>$(NULL) || true
	$(CXX) $(CXXFLAGS) -c $< -o $@

# ============================================================
# Clean
# ============================================================
clean:
	-@if exist $(OBJDIR) $(RMDIR) $(OBJDIR) 2>$(NULL) || true
	-@if exist $(TARGET) $(RM) $(TARGET) 2>$(NULL) || true
	-@if exist output_*.csv $(RM) output_*.csv 2>$(NULL) || true
	-@if exist results_FVM.png $(RM) results_FVM.png 2>$(NULL) || true

# ============================================================
# Run
# ============================================================
run: $(TARGET)
	./$(TARGET)

# ============================================================
# Help
# ============================================================
help:
	@echo "Targets disponibles :"
	@echo "  all    : Compiler (par défaut)"
	@echo "  clean  : Supprimer les fichiers compilés et les résultats"
	@echo "  run    : Compiler et lancer la simulation"
	@echo "  help   : Afficher cette aide"

.PHONY: all clean run help