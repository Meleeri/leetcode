.PHONY: clean All

All:
	@echo "----------Building project:[ Permutation_Sequence - Debug ]----------"
	@cd "Permutation_Sequence" && $(MAKE) -f  "Permutation_Sequence.mk"
clean:
	@echo "----------Cleaning project:[ Permutation_Sequence - Debug ]----------"
	@cd "Permutation_Sequence" && $(MAKE) -f  "Permutation_Sequence.mk" clean
