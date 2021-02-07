OUTDIR = $(shell pwd)
TEX = pdflatex -shell-escape -interaction=nonstopmode -file-line-error
PDFTEX = pdflatex -shell-escape -interaction=nonstopmode -file-line-error
PDFOUT = The_C_Language
PDF_TARGET = $(addsuffix .pdf, $(PDFOUT))
LATEXIN = main.tex

all: pdf

pdf: $(PDF_TARGET)

$(PDF_TARGET): $(LATEXIN)
	$(PDFTEX) -output-directory=$(OUTDIR) -jobname=$(PDFOUT) $(LATEXIN)
	$(PDFTEX) -output-directory=$(OUTDIR) -jobname=$(PDFOUT) $(LATEXIN)
	sudo cp $(PDF_TARGET) /var/www/html/pdf/$(PDF_TARGET)
	echo -e "\033[92m Target Made Successfully \033[0m"

clean:
	rm  -f *.pdf *.aux *.dvi *.log *.toc
