.PHONY: clean All

All:
	@echo "----------Building project:[ Add_Two_Numbers - Debug ]----------"
	@cd "Add_Two_Numbers" && $(MAKE) -f  "Add_Two_Numbers.mk"
clean:
	@echo "----------Cleaning project:[ Add_Two_Numbers - Debug ]----------"
	@cd "Add_Two_Numbers" && $(MAKE) -f  "Add_Two_Numbers.mk" clean
