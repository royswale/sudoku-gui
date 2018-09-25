#pragma once

#include "sudoku_ffi/src/sudoku_ffi/sudoku.h"
#include <QFrame>

class SudokuCellWidget;

enum class Direction {
    Left, Right, Up, Down
};

using Candidates = std::array<uint16_t, 81>;

class SudokuGridWidget final : public QFrame {
    Q_OBJECT

    std::array<SudokuCellWidget*, 81> m_cells;
    std::vector<Candidates> m_candidates;
    int m_highlighted_digit = 0; // 1-9, 0 for no highlight

    // TODO: make private again
    public:
        std::vector<Sudoku> m_sudoku;

    private:
        auto current_sudoku() -> Sudoku&;
        auto current_candidates() -> Candidates&;
        auto push_savepoint() -> void;
        auto pop_savepoint() -> void;
        auto update_cells() -> void;

    public:
        explicit SudokuGridWidget(QWidget *parent = 0);

        auto sudoku() -> Sudoku;
        auto generate_major_lines() -> void;
        auto generate_minor_lines() -> void;
        auto generate_cells() -> void;
        auto set_clues() -> void;

        auto compute_candidates() -> void;
        auto recompute_candidates() -> void;

        auto move_focus(int current_cell, Direction direction) -> void;

        auto insert_entry(Entry entry) -> void;
        auto set_candidate(Entry entry, bool is_possible) -> void;
        auto undo() -> bool;

    public slots:
        void highlight_digit(int digit);
};