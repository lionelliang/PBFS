RM := rm -rf

all: BFS

# Tool invocations
BFS: 
	g++ -Wall -fopenmp -o BFSOpenMP  BFSOpenMP.cpp
	g++ -Wall -fopenmp -o BFSSequence BFSSequence.cpp
	@echo 'Finished building target: $@'

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) BFS
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:
