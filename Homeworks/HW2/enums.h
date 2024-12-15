/******************************************
*                                         *
*               PROTCAD                   *
*     PROTein Computer Assisted Design    *
*                                         *
*          Copyright 2002,2011            *
*        Christopher Mark Summa           *
*                 and                     *
*    The University of New Orleans        *
*       New Orleans, LA 70148             *
*                                         *
******************************************/

#ifndef ENUMS_H
#define ENUMS_H

enum axis {X_axis, Y_axis, Z_axis};

enum resultFlag {unrecoverableFail, recoverableFail, success};

enum PCRotamer {PC_non_rotamer, PC_gauche_plus, PC_trans, PC_gauche_minus};

enum PCStopIterationLevel {PC_RESIDUE, PC_CHAIN, PC_MOLECULE, PC_ENSEMBLE};

enum PCMoleculeType {PC_protein,
            PC_DNA,
            PC_RNA,
            PC_ligand,
            PC_solvent,
            PC_unknown  };

enum PCPotentialType {PC_nonBondedPotential,
            PC_torsonalPotential};

enum PCNonBondedPotentialType {PC_pairwiseAtomPotential,
            PC_nonPairwiseAtomPotential,
            PC_pairwiseResiduePotential,
            PC_nonPairwiseResiduePotential,
            PC_mixedPotential};

enum PCBondTopologyType {PC_nonbonded,
            PC_same_atom,
            PC_one_two_bonded,
            PC_one_three_bonded,
            PC_one_four_bonded,
            PC_one_five_bonded};

enum PCActivationType {PC_backbone,
                       PC_sidechain,
                       PC_rigid_body,
                       PC_threading};

#endif
