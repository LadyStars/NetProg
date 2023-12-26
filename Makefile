.PHONY: clean All

All:
	@echo "----------Building project:[ echo - Debug ]----------"
	@cd "echo" && "$(MAKE)" -f  "echo.mk"
clean:
	@echo "----------Cleaning project:[ echo - Debug ]----------"
	@cd "echo" && "$(MAKE)" -f  "echo.mk" clean
