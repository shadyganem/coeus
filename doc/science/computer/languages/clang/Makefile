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
	rm  -f *.tdo *.aux *.dvi *.log *.toc *.out
	echo -e "\033[92mcopying PDF to web server\033[0m"
	sudo cp $(PDF_TARGET) /var/www/html/pdf/$(PDF_TARGET)
	echo -e "\033[92mTarget Made Successfully \033[0m"

clean:
	rm  -f *.pdf *.aux *.dvi *.log *.toc *.out *.tdo
