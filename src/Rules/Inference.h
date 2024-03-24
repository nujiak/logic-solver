#ifndef LOGIC_SOLVER_INFERENCE_H
#define LOGIC_SOLVER_INFERENCE_H

#include <memory>
#include "Propositions/WellFormedFormula.h"

class Inference : public WellFormedFormula {
protected:
    std::shared_ptr<WellFormedFormula> resultantProposition;

    explicit Inference(const std::shared_ptr<WellFormedFormula> &resultantProposition)
            : resultantProposition(resultantProposition) {}

    Inference() = default;

public:
    bool operator==(const std::shared_ptr<WellFormedFormula> &other) const override;

    [[nodiscard]] std::string getString() const override;

    [[nodiscard]] std::shared_ptr<WellFormedFormula> getProposition() const;
};


#endif //LOGIC_SOLVER_INFERENCE_H
