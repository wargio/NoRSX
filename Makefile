#---------------------------------------------------------------------------------
# Clear the implicit built in rules
#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------
all:
	@$(MAKE) -C libNoRSX --no-print-directory
	@$(MAKE) -C NoRSX_Example pkg --no-print-directory

clean:
	@$(MAKE) -C libNoRSX clean --no-print-directory
	@$(MAKE) -C NoRSX_Example clean --no-print-directory
