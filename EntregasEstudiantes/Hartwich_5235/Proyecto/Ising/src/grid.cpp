# include "ising_public_interface.h"

// Operators that grant access to the flattened 1D vector using the normal 2D indices.

/* read-write */
int& Grid::operator()(int i, int j, char mode, char check_bounds) {
    if (mode == 'p') { // p-eriodic boundary condition: maps N to 0 and -1 to N-1 
        i = (i + n_rows_) % n_rows_;
        j = (j + n_cols_) % n_cols_;
    }
    if (check_bounds == 'n')  // significantly faster than using .at and our additional bounds checking. Tested the implementation in 'safe mode', then changed to this one.
        return data_[i * n_cols_ + j];
    else {
        if (i < 0 || i >= n_rows_ || j < 0 || j >= n_cols_)
            throw std::out_of_range("Invalid [i, j] index");
        return data_.at(i * n_cols_ + j);
    }
}

/* read-only */
int Grid::operator()(int i, int j, char mode, char check_bounds) const {
    if (mode == 'p') { // p-eriodic boundary condition: maps N to 0 and -1 to N-1 
        i = (i + n_rows_) % n_rows_;
        j = (j + n_cols_) % n_cols_;
    }
    if (check_bounds == 'n')
        return data_[i * n_cols_ + j]; 
    else {
        if (i < 0 || i >= n_rows_ || j < 0 || j >= n_cols_)
            throw std::out_of_range("Invalid [i, j] index");
        return data_.at(i * n_cols_ + j);
    }
}


