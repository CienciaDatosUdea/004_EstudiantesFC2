#include <random>
#include <cmath>
#include <fstream>

#include "system.h"


Particle::Particle(double x_, double y_,double vx_, double vy_, double m_):x(x_),y(y_),vx(vx_), vy(vy_), fx(0), fy(0), m(m_){}

void Particle::update(float dt,GridBin &grid, double r_cut){
    //euler (terrible 0/10 not recomended)
    // vx += fx*dt;
    // vy += fy*dt;
    // x +=  vx*dt;
    // y +=  vy*dt;
    //verlet integrator
    // x += vx * dt + fx/m * (dt*dt*0.5);
    // y += vy * dt + fy/m * (dt*dt*0.5);
    // double oldfx = fx;
    // double oldfy = fy;
    // applyForces(grid,r_cut);
    // vx += (oldfx+fx)*0.5*dt/m;
    // vy += (oldfy+fy)*0.5*dt/m;
    double vx_h = vx + 0.5* dt * fx / m;
    double vy_h = vy + 0.5* dt * fy / m;
    x += vx_h * dt;
    y += vy_h * dt;
    applyForces(grid,r_cut);
    vx = vx_h + 0.5 * dt* fx/m;
    vy = vy_h + 0.5 * dt * fy/m;


    int rows = grid.rows;
    int cols = grid.cols;
    if (y <= 1) { y = 1; vy *= -1; }
    if (y >= rows - 2) { y = rows - 2; vy *= -1; }
    if (x <= 1) { x = 1; vx *= -1; }
    if (x >= cols - 2) { x = cols - 2; vx *= -1; }
}

void Particle::applyForces(GridBin& grid, double r_cut){
    fx = 0;
    fy = 0;
    // gravity(*this);
    auto neigh = grid.getNeighbors(this, r_cut);
    for (auto* q:neigh ){
        lennardJones(*this,*q,1,0.89,r_cut);
        // wcaPotential(*this,*q,0.1,0.8);
        // lennardJonesWithLimit(*this,*q,1,1,10,2500);
        // interact(*this, *q);
    }

}
double Particle::getKinetic(){
    return 0.5 * m * (vx * vx + vy * vy);
}

double Particle::getPotential(GridBin & grid,double r_cut){
    double PE = 0;
    auto neighbors = grid.getNeighbors(this, r_cut);
    
    for(auto* neighbor : neighbors) {
        // Only count each pair once (i < j)
        if(this < neighbor) {
            double dx = neighbor->x - this->x;
            double dy = neighbor->y - this->y;
            double r2 = dx*dx + dy*dy;
            
            // if(r2 > 10*10 || r2 < 1e-10) continue;
            
            double r = std::sqrt(r2);
            double sr = 1 / r;
            double sr6 = sr*sr*sr * sr*sr*sr;
            double sr12 = sr6 * sr6;
            
            // LJ potential: 4*epsilon*(sr12 - sr6)
            PE += 4.0 * (sr12 - sr6);
        }

    }
    return PE;
}


GridBin::GridBin(int r, int c, int b): rows(r), cols(c), binSize(b){
    int br = (rows+binSize-1)/binSize;
    int bc = (cols+binSize-1)/binSize;
    bins.resize(br,std::vector<std::vector<Particle*>>(bc));
}

void GridBin::clear(){
    for(auto& row: bins){
        for(auto& cell: row){
            cell.clear();
        }
    }
}

void GridBin::insert(Particle *p){
    int br = static_cast<int>(p->y) / binSize;
    int bc = static_cast<int>(p->x) / binSize;
    bins[br][bc].push_back(p);

}

std::vector<Particle*> GridBin::getNeighbors(Particle* p, float radius){
    std::vector<Particle*> result;
    int br = static_cast<int>(p->y) / binSize;
    int bc = static_cast<int>(p->x) / binSize;

    for(int dr= -1;dr<=1;dr++){
        for (int dc = -1; dc<=1; dc++){
            int nr = br + dr;
            int nc = bc + dc;
            if (nr<0 || nc<0 || nr>= (int)bins.size() || nc >= (int)bins[0].size()) continue;
            for (auto* q: bins[nr][nc]){
                if (q != p){
                    double dx = q->x - p->x;
                    double dy = q->y - p->y;
                    if(dx*dx+dy*dy<=radius*radius) result.push_back(q);
                }
            }
        }
    }
    return result;
}

System::System(int N_, GridBin & G, double T_, double m_, double kb_, double r): N(N_),grid(G), T(T_), m(m_), kb(kb_), r_cut(r) {
    double sigmaT = std::sqrt(kb* T / m);
    particles.reserve(N);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::normal_distribution<double> normal(0.0, sigmaT);
    std::uniform_real_distribution<double> uniform(0, 2.0);  // For initial spacing


    const double min_spacing = 2.0;  // 20% extra space
    
    

    for(int i = 0; i < N; i++) {
        int attempts = 0;
        double x, y;
        bool valid_position = false;
        
        while (!valid_position && attempts < 1000) {
            x = min_spacing + (grid.cols - 2 * min_spacing) * (gen() / static_cast<double>(gen.max()));
            y = min_spacing + (grid.rows - 2 * min_spacing) * (gen() / static_cast<double>(gen.max()));
            
            valid_position = true;
            for (const auto& p : particles) {
                double dx = p.x - x;
                double dy = p.y - y;
                if (dx*dx + dy*dy < min_spacing * min_spacing) {
                    valid_position = false;
                    break;
                }
            }
            attempts++;
        }
        
        double vx = normal(gen);
        double vy = normal(gen);
        particles.emplace_back(x, y, vx, vy,m);
    }
}


void System::update(double dt,std::ofstream *file){
        grid.clear();
        for(auto& p: particles){
            grid.insert(&p);
        }

        for(auto& p: particles){
            p.update(dt,grid,r_cut);
            if(file) *file<< p.x << "\t" << p.y << "\n";
        }
}

double System::getEnergy(){
    double E = 0;
    for(auto &p: particles){
        E += p.getKinetic() + p.getPotential(grid,r_cut);
    }
    return E;

}

double System::getTemperature(){
    double EK = 0;
    for(auto &p: particles){
        EK += p.getKinetic();

    }
    return EK / (N*kb);

}

void System::rescaleTemp(){
    double current_T = getTemperature();
    if (current_T > 0) {
        double scale = std::sqrt(T / current_T);
        
        // Rescale all velocities
        for(auto& p : particles) {
            p.vx *= scale;
            p.vy *= scale;
        }
    }
}

void lennardJones(Particle& p1, Particle& p2, float epsilon, float sigma, float cutoff){
    double dx = p2.x-p1.x;
    double dy = p2.y-p1.y;
    double r2 = dx*dx + dy*dy;

    if (r2> cutoff*cutoff && r2<1e-10) return;

    double sr2 = (sigma*sigma)/r2;
    double sr6 = sr2*sr2*sr2;
    double sr12 = sr6*sr6;

    double fmag = (24*epsilon /r2) * (2*sr12-sr6);

    double fx = fmag * dx;
    double fy = fmag * dy;

    p1.fx -= fx;
    p1.fy -= fy;
}

void wcaPotential(Particle& p1, Particle& p2, double epsilon, double sigma) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double r2 = dx*dx + dy*dy;
    double r = std::sqrt(r2);
    
    if (r > sigma * std::pow(2.0, 1.0/6.0) || r < .1) 
        return;
    
    double sr = sigma / r;
    double sr6 = sr*sr*sr * sr*sr*sr;
    double sr12 = sr6 * sr6;
    
    double force_magnitude = 24.0 * epsilon * (2.0 * sr12 - sr6) / r;
    
    p1.fx += force_magnitude * dx / r;
    p1.fy += force_magnitude * dy / r;
    p2.fx -= force_magnitude * dx / r;
    p2.fy -= force_magnitude * dy / r;
}

void lennardJonesWithLimit(Particle& p1, Particle& p2, double epsilon, double sigma, 
                          double cutoff, double max_force) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    double r2 = dx*dx + dy*dy;
    
    if (r2 < 10e-10 || r2 > cutoff * cutoff) 
        return;
    
    double r = std::sqrt(r2);
    double sr = sigma / r;
    double sr6 = sr*sr*sr * sr*sr*sr;
    double sr12 = sr6 * sr6;
    
    double force_magnitude = 24.0 * epsilon * (2.0 * sr12 - sr6) / r;
    
    // Force limiting to prevent explosions
    if (std::abs(force_magnitude) > max_force) {
        force_magnitude = (force_magnitude > 0) ? max_force : -max_force;
    }
    
    p1.fx += force_magnitude * dx / r;
    p1.fy += force_magnitude * dy / r;
    p2.fx -= force_magnitude * dx / r;
    p2.fy -= force_magnitude * dy / r;
}

void interact(Particle &p1, Particle &p2){
    double dx = p2.x-p1.x;
    double dy = p2.y-p1.y;
    if(dx*dx+dy*dy<1){
        std::swap(p1.vx,p2.vx);
        std::swap(p1.vy,p2.vy);
    }

}
void gravity(Particle &p1){
    p1.fx = 0;
    p1.fy = -p1.m * 9.81;
}

void velocity_rescaling(std::vector<Particle>& particles, double target_T, const float KB) {
    double total_ke = 0.0;
    int n_particles = particles.size();
    
    // Calculate current kinetic energy
    for(const auto& p : particles) {
        total_ke += 0.5 * p.m * (p.vx*p.vx + p.vy*p.vy);
    }
    
    // Calculate current temperature (2D: 2 degrees of freedom per particle)
    double current_T = total_ke / (n_particles * KB);
    
    if (current_T > 0) {
        double scale = std::sqrt(target_T / current_T);
        
        // Rescale all velocities
        for(auto& p : particles) {
            p.vx *= scale;
            p.vy *= scale;
        }
    }
}