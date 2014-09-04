.PHONY: clean All

All:
	@echo "----------Building project:[ Candy - Debug ]----------"
	@cd "Candy" && $(MAKE) -f  "Candy.mk"
clean:
	@echo "----------Cleaning project:[ Candy - Debug ]----------"
	@cd "Candy" && $(MAKE) -f  "Candy.mk" clean
