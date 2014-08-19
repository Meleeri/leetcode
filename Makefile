.PHONY: clean All

All:
	@echo "----------Building project:[ Max_Points_on_a_Line - Debug ]----------"
	@cd "Max_Points_on_a_Line" && $(MAKE) -f  "Max_Points_on_a_Line.mk"
clean:
	@echo "----------Cleaning project:[ Max_Points_on_a_Line - Debug ]----------"
	@cd "Max_Points_on_a_Line" && $(MAKE) -f  "Max_Points_on_a_Line.mk" clean
