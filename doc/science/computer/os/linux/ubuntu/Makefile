OUTDIR = $(shell pwd)
TEX = pdflatex -shell-escape -interaction=nonstopmode -file-line-error
PDFTEX = pdflatex -shell-escape -interaction=nonstopmode -file-line-error
PDFOUT = ubuntu
PDF_TARGET = $(addsuffix .pdf, $(PDFOUT))
LATEXIN = main.tex

all: pdf

pdf: $(PDF_TARGET)

$(PDF_TARGET): $(LATEXIN)
	$(PDFTEX) -output-directory=$(OUTDIR) -jobname=$(PDFOUT) $(LATEXIN)
	$(PDFTEX) -output-directory=$(OUTDIR) -jobname=$(PDFOUT) $(LATEXIN)
	echo -e "\033[92m Target Made Successfully \033[0m"

clean:
	rm  -f *.pdf *.aux *.dvi *.log *.toc
