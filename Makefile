.PHONY: clean All

All:
	@echo "----------Building project:[ Binary_Tree_Postorder_Traversal - Debug ]----------"
	@cd "Binary_Tree_Postorder_Traversal" && $(MAKE) -f  "Binary_Tree_Postorder_Traversal.mk"
clean:
	@echo "----------Cleaning project:[ Binary_Tree_Postorder_Traversal - Debug ]----------"
	@cd "Binary_Tree_Postorder_Traversal" && $(MAKE) -f  "Binary_Tree_Postorder_Traversal.mk" clean
